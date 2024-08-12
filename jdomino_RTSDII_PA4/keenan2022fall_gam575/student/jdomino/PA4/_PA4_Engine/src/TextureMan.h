//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H 

#include "ManBase.h"
#include "Texture.h"
#include "meshData.h"

class TextureMan : public ManBase
{
	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
public:
	static void Create(int reserveNum = 0, int reserveGrow = 1);
	static void Destroy();
	static Texture *Add(const char *const pName, Texture::Name name);
    static void Add(Texture::Name name, Texture *pTexture);
    static Texture *Add(meshData &mB);
	static Texture *Find(Texture::Name name);
	static GLuint FindID(Texture::Name name);
	static void Remove(Texture *pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static TextureMan *privGetInstance();

	~TextureMan();
	TextureMan(int reserveNum, int reserveGrow);

	void privLoadTexture(const char *const pName, GLuint *&textureID);
    void privLoadTexture(meshData &mB, GLuint *&textureID);
    bool privLoadRawTexture(meshData &mB);
    bool privLoadTGATexture(const char *szFileName, 
        GLint minFilter, 
        GLint magFilter, 
        GLint wrapModeS,
        GLint wrapModeT
        );
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------
protected:
	DLink *derivedCreateNode() override;


	//----------------------------------------------------------------------
	// Data: unique data for this manager 
	//----------------------------------------------------------------------
private:
	Texture *poNodeCompare;
	static TextureMan *posInstance;

};


#endif