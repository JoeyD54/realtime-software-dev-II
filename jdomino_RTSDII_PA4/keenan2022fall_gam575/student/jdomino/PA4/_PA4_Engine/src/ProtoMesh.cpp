//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "meshData.h"

#include "ProtoMesh.h"
#include "File.h"
#include "MeshFileHdr.h"
#include "TextureMan.h"

using namespace Azul;

void ProtoMesh::privCreateVAO(const char *const pMeshFileName, Texture *&pTexture)
{
	// future proofing it for a file
	assert(pMeshFileName);
	AZUL_UNUSED_VAR(pMeshFileName);

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);   // <--- Active

	// Create a VBO
	glGenBuffers(1, &this->vbo_verts);
	assert(this->vbo_verts != 0);

	glGenBuffers(1, &this->vbo_norms);
	assert(this->vbo_norms != 0);

	glGenBuffers(1, &this->vbo_texts);
	assert(this->vbo_texts != 0);

	glGenBuffers(1, &this->vbo_index);
	assert(this->vbo_index != 0);

	// File stuff
	File::Handle fh;
	File::Error  ferror;

	// create a header
	MeshFileHdr meshHdr;

	// ----------------------------------------------
	// READ the data from the file ONLY
	// ----------------------------------------------

	const char* pPath = "Data\\";
	size_t size = strlen(pPath) + strlen(pMeshFileName) + 1;
	char* pfileName = new char[size]();
	memset(pfileName, 0, size);
	strcat_s(pfileName, size, pPath);
	strcat_s(pfileName, size, pMeshFileName);

	ferror = File::Open(fh, pfileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Get the size
	ferror = File::Seek(fh, File::Position::END, 0);
	assert(ferror == File::Error::SUCCESS);

	DWORD length;
	ferror = File::Tell(fh, length);
	assert(ferror == File::Error::SUCCESS);
	
	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	char *poBuff = new char[length];
	assert(poBuff);

	ferror = File::Read(fh, poBuff, length);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	std::string strIn(poBuff, length);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);
	mB.Print("mB");

	delete[] poBuff;

	// General stuff
	assert(mB.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	this->numTris = (int)mB.triCount;
	this->numVerts = (int)mB.vertCount;

	delete pfileName;

	assert(this->numTris > 0);
	assert(this->numVerts > 0);

	// Load the verts data: ---------------------------------------------------------
	assert(mB.vbo_vert.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

	// load the data to the GPU
	assert(mB.vbo_vert.poData);
	assert(mB.vbo_vert.dataSize > 0);
	assert(mB.vbo_vert.count * sizeof(Vert_xyz) == mB.vbo_vert.dataSize);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_vert.dataSize), mB.vbo_vert.poData, GL_STATIC_DRAW);

	// Vert data is location: 0  (used in vertex shader)
	assert(0 == mB.vbo_vert.attribIndex);
	assert(mB.vbo_vert.vboType == vboData::VBO_TYPE::VEC3);
	assert(mB.vbo_vert.componentType == vboData::VBO_COMPONENT::FLOAT);
	glVertexAttribPointer(mB.vbo_vert.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(mB.vbo_vert.attribIndex);

	// Load the norms data: ---------------------------------------------------------

	assert(mB.vbo_norm.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

	// load the data to the GPU
	assert(mB.vbo_norm.poData);
	assert(mB.vbo_norm.dataSize > 0);
	assert(mB.vbo_norm.count * sizeof(Vert_NxNyNz) == mB.vbo_norm.dataSize);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_norm.dataSize), mB.vbo_norm.poData, GL_STATIC_DRAW);

	// normals data in location 1 (used in vertex shader)
	assert(1 == mB.vbo_norm.attribIndex);
	assert(mB.vbo_norm.vboType == vboData::VBO_TYPE::VEC3);
	assert(mB.vbo_norm.componentType == vboData::VBO_COMPONENT::FLOAT);
	glVertexAttribPointer(mB.vbo_norm.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(mB.vbo_norm.attribIndex);

	// Load the texts data: ---------------------------------------------------------
	assert(mB.vbo_uv.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);

	// load the data to the GPU
	assert(mB.vbo_uv.poData);
	assert(mB.vbo_uv.dataSize > 0);
	assert(mB.vbo_uv.count * sizeof(Vert_uv) == mB.vbo_uv.dataSize);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_uv.dataSize), mB.vbo_uv.poData, GL_STATIC_DRAW);

	// Texture data is location: 2  (used in vertex shader)
	assert(2 == mB.vbo_uv.attribIndex);
	assert(mB.vbo_uv.vboType == vboData::VBO_TYPE::VEC2);
	assert(mB.vbo_uv.componentType == vboData::VBO_COMPONENT::FLOAT);
	glVertexAttribPointer(mB.vbo_uv.attribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(mB.vbo_uv.attribIndex);

	// Load the index data: ---------------------------------------------------------

	// Bind our 2nd VBO as being the active buffer and storing index ) 
	assert(mB.vbo_index.targetType == vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

	// Copy the index data to our buffer 
	assert(mB.vbo_index.vboType == vboData::VBO_TYPE::SCALAR);
	assert(mB.vbo_index.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
	assert(mB.vbo_index.dataSize > 0);
	assert(mB.vbo_index.poData);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_index.dataSize), mB.vbo_index.poData, GL_STATIC_DRAW);

	// ------------------------------------------------------
	// Load the texture - hopefully
	// ------------------------------------------------------

	pTexture = TextureMan::Add(mB);
	assert(pTexture);


}

ProtoMesh::ProtoMesh(const char *const pMeshFileName, Texture *&pTexture)
	: Mesh()
{
	assert(pMeshFileName);
	this->privCreateVAO(pMeshFileName, pTexture);
	assert(pTexture);
}

ProtoMesh::~ProtoMesh()
{
	// remove anything dynamic here
}


// --- End of File ---
