//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TextureMan.h"
#include "TGA.h"
#include "textureDataOpenGL.h"
#include "File.h"

using namespace Azul;

TextureMan *TextureMan::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
TextureMan::TextureMan(int reserveNum, int reserveGrow)
	: ManBase(reserveGrow)
{
	// Preload the reserve
	this->proFillReservedPool(reserveNum);

	// initialize derived data here
	this->poNodeCompare = new Texture();
}

TextureMan::~TextureMan()
{
	delete this->poNodeCompare;
	this->poNodeCompare = nullptr;

	// iterate through the list and delete
	Iterator *pIt = this->baseGetActiveIterator();

	DLink *pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Texture *pDeleteMe = (Texture *)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}

	pIt = this->baseGetReserveIterator();

	pNode = pIt->First();

	// Walk through the nodes
	while (!pIt->IsDone())
	{
		Texture *pDeleteMe = (Texture *)pIt->Curr();
		pNode = pIt->Next();
		delete pDeleteMe;
	}
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void TextureMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum >= 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(posInstance == nullptr);

	// Do the initialization
	if (posInstance == nullptr)
	{
		posInstance = new TextureMan(reserveNum, reserveGrow);
	}

}

void TextureMan::Destroy()
{
	TextureMan *pMan = TextureMan::privGetInstance();
	assert(pMan != nullptr);
	AZUL_UNUSED_VAR(pMan);

	delete TextureMan::posInstance;
	TextureMan::posInstance = nullptr;
}
void TextureMan::Add(Texture::Name _name, Texture *pTexture )
{
    assert(pTexture);
    pTexture->name = _name;
}

Texture *TextureMan::Add(meshData &mB)
{
    TextureMan *pMan = TextureMan::privGetInstance();

    GLuint               textureID;
    GLuint *pTextureID = &textureID;

    // Load the texture and get the textureID
    pMan->privLoadTexture(mB, pTextureID);

    Texture *pNode = (Texture *)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    pNode->Set
    ( 
        mB.text_color.pFileName,
        Texture::Name::PROTO_LOAD,
        textureID,
        textureDataOpenGL::Get(mB.text_color.minFilter),
        textureDataOpenGL::Get(mB.text_color.magFilter),
        textureDataOpenGL::Get(mB.text_color.wrapS),
        textureDataOpenGL::Get(mB.text_color.wrapT)
    );

    return pNode;
}


Texture *TextureMan::Add(const char *const pMeshFileName, Texture::Name name)
{
    TextureMan *pMan = TextureMan::privGetInstance();

    GLuint               textureID;
    GLuint *pTextureID = &textureID;

    // Load the texture and get the textureID

    // -------------------------------
    // Read and recreate model data
    // -------------------------------

    File::Handle fh;
    File::Error err;



	assert(pMeshFileName);
	const char *pPath = "Data\\";
	size_t size = strlen(pPath) + strlen(pMeshFileName) + 1;
	char *pFileName = new char[size]();
	memset(pFileName, 0, size);
	strcat_s(pFileName, size, pPath);
	strcat_s(pFileName, size, pMeshFileName);


    err = File::Open(fh, pFileName, File::Mode::READ);
    assert(err == File::Error::SUCCESS);

	delete[] pFileName;

    err = File::Seek(fh, File::Position::END, 0);
    assert(err == File::Error::SUCCESS);

    DWORD FileLength;
    err = File::Tell(fh, FileLength);
    assert(err == File::Error::SUCCESS);

    char *poNewBuff = new char[FileLength]();
    assert(poNewBuff);

    err = File::Seek(fh, File::Position::BEGIN, 0);
    assert(err == File::Error::SUCCESS);

    err = File::Read(fh, poNewBuff, FileLength);
    assert(err == File::Error::SUCCESS);

    err = File::Close(fh);
    assert(err == File::Error::SUCCESS);

    std::string strIn(poNewBuff, FileLength);
    meshData_proto mB_proto;

    mB_proto.ParseFromString(strIn);

    meshData mB;
    mB.Deserialize(mB_proto);
    mB.Print("mB");

    delete[] poNewBuff;

    pMan->privLoadTexture(mB, pTextureID);

    Texture *pNode = (Texture *)pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the date
    pNode->Set
    (
        mB.text_color.pFileName,
        name,
        textureID,
        textureDataOpenGL::Get(mB.text_color.minFilter),
        textureDataOpenGL::Get(mB.text_color.magFilter),
        textureDataOpenGL::Get(mB.text_color.wrapS),
        textureDataOpenGL::Get(mB.text_color.wrapT)
    );

    return pNode;
}



Texture *TextureMan::Find(Texture::Name _name)
{
	TextureMan *pMan = TextureMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->name = _name;

	Texture *pData = (Texture *)pMan->baseFind(pMan->poNodeCompare);
	return pData;
}

GLuint TextureMan::FindID(Texture::Name name)
{
	TextureMan *pMan = TextureMan::privGetInstance();
	assert(pMan != nullptr);

    Texture *pTexture = pMan->Find(name);
    if(pTexture == nullptr)
    {
        pTexture = pMan->Find(Texture::Name::HOT_PINK);
    }

	return pTexture->textureID;
}

void TextureMan::Remove(Texture *pNode)
{
	assert(pNode != nullptr);

	TextureMan *pMan = TextureMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->baseRemove(pNode);
}

void TextureMan::Dump()
{
	TextureMan *pMan = TextureMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
TextureMan *TextureMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(posInstance != nullptr);

	return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink *TextureMan::derivedCreateNode()
{
	DLink *pNodeBase = new Texture();
	assert(pNodeBase != nullptr);

	return pNodeBase;
}

void TextureMan::privLoadTexture(meshData &mB, GLuint *&textureID)
{
    // Get an ID, for textures (OpenGL poor man's handle)
    glGenTextures(1, textureID);

    // Bind it.
    glBindTexture(GL_TEXTURE_2D, *textureID);

    // Loat the texture
    assert(mB.text_color.as_is == false);
    this->privLoadRawTexture(mB);
}



void TextureMan::privLoadTexture(const char *const _assetName, GLuint *&textureID)
{
	// Get an ID, for textures (OpenGL poor man's handle)
	glGenTextures(1, textureID);

	// Bind it.
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Loat the texture
    this->privLoadTGATexture(_assetName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

bool TextureMan::privLoadRawTexture( meshData &mB )
{
    void *pBits = mB.text_color.poData;
    assert(pBits);

    int nWidth = (int)mB.text_color.width;
    int nHeight = (int)mB.text_color.height;
 
    // Hard to verify.. best guess.. input RGBA, output RGBA
    int nComponents = this->privGetOpenGLValue(mB.text_color.nComponent);
    GLenum eFormat = this->privGetOpenGLValue(mB.text_color.eFormat);

    GLint minFilter = (GLint)textureDataOpenGL::Get(mB.text_color.minFilter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)textureDataOpenGL::Get(mB.text_color.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)textureDataOpenGL::Get(mB.text_color.wrapT));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)textureDataOpenGL::Get(mB.text_color.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)textureDataOpenGL::Get(mB.text_color.magFilter));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

    if(minFilter == GL_LINEAR_MIPMAP_LINEAR ||
        minFilter == GL_LINEAR_MIPMAP_NEAREST ||
        minFilter == GL_NEAREST_MIPMAP_LINEAR ||
        minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

GLenum TextureMan::privGetOpenGLValue(textureData::TEXTURE_EFORMAT eFormat) const
{
    GLenum val = 0;

    switch(eFormat)
    {
    case textureData::TEXTURE_EFORMAT::EFORMAT_BGR:
        val = GL_BGR;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_BGRA:
        val = GL_BGRA;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_RGB:
        val = GL_RGB;
        break;

    case textureData::TEXTURE_EFORMAT::EFORMAT_RGBA:
        val = GL_RGBA;
        break;

    default:
        assert(false);
    }

    return val;
}

GLint TextureMan::privGetOpenGLValue(textureData::TEXTURE_NCOMPONENT nComponent) const
{
    GLint val = 0;

    switch(nComponent)
    {
    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR:
        val = GL_BGR;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA:
        val = GL_BGRA;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB:
        val = GL_RGB;
        break;

    case textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA:
        val = GL_RGBA;
        break;

    default:
        assert(false);
    }

    return val;
}


// Load a TGA as a 2D Texture. Completely initialize the state
bool TextureMan::privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == nullptr)
	{
		return false;
	}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) wrapModeS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) wrapModeT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
		glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}


//-----------------------------------------------------------------------------
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
//-----------------------------------------------------------------------------
GLbyte *TextureMan::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte *pBits = NULL;          // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file

	assert(szFileName);
	const char *pPath = "Data\\";
	size_t size = strlen(pPath) + strlen(szFileName) + 1;
	char *pFileName = new char[size]();
	memset(pFileName, 0, size);
	strcat_s(pFileName, size, pPath);
	strcat_s(pFileName, size, szFileName);

	fopen_s(&pFile, pFileName, "rb");
	assert(pFile);
	
	delete[] pFileName;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte *)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{

	case 3:     // Most likely case
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;

	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		// bad case - keenan
		// i commented out
	  //  *eFormat = GL_LUMINANCE;
	  //  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
		// If on the iPhone, TGA's are BGR, and the iPhone does not 
		// support BGR without alpha, but it does support RGB,
		// so a simple swizzle of the red and blue bytes will suffice.
		// For faster iPhone loads however, save your TGA's with an Alpha!

		break;
	}


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

