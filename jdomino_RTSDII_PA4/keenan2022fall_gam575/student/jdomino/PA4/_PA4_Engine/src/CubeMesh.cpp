//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CubeMesh.h"
#include "File.h"
#include "MeshFileHdr.h"

using namespace Azul;

void CubeMesh::privCreateVAO(const char *const pMeshFileName)
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

	glGenBuffers(1, &this->vbo_texts);
	assert(this->vbo_texts != 0);

	glGenBuffers(1, &this->vbo_norms);
	assert(this->vbo_norms != 0);

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

	assert(pMeshFileName);
	const char *pPath = "Data\\";
	size_t size = strlen(pPath) + strlen(pMeshFileName) + 1;
	char *pFileName = new char[size]();
	memset(pFileName, 0, size);
	strcat_s(pFileName, size, pPath);
	strcat_s(pFileName, size, pMeshFileName);

	ferror = File::Open(fh, pFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	delete[] pFileName;

	// Read the Hdr
	ferror = File::Read(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	// Using the hdr, allocate the space for the buffers
	this->numVerts = meshHdr.numVerts;
	this->numTris = meshHdr.numTriList;

	// allocate buffers
	Vert_xyz *pCubeData_xyz = new Vert_xyz[(unsigned int)meshHdr.numVerts];
	assert(pCubeData_xyz);
	Vert_uv *pCubeData_uv = new Vert_uv[(unsigned int)meshHdr.numVerts];
	assert(pCubeData_uv);
	Vert_NxNyNz *pCubeData_NxNyNz = new Vert_NxNyNz[(unsigned int)meshHdr.numVerts];
	assert(pCubeData_NxNyNz);
	Tri_index *pTriList = new Tri_index[(unsigned int)meshHdr.numTriList];
	assert(pTriList);

	// Read verts
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, pCubeData_xyz, sizeof(Vert_xyz) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, pCubeData_uv, sizeof(Vert_uv) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, pCubeData_NxNyNz, sizeof(Vert_uv) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, pTriList, sizeof(Tri_index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	// --------------------------------------------------------------
	// Data is in RAM... Configure and send data to GPU
	// --------------------------------------------------------------

		// Load the verts data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->numVerts), pCubeData_xyz, GL_STATIC_DRAW);

	// Vert data is location: 0  (used in vertex shader)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Load the texts data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);
	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->numVerts), pCubeData_uv, GL_STATIC_DRAW);

	// Texture data is location: 2  (used in vertex shader)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Load the norms data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_NxNyNz) * this->numVerts), pCubeData_NxNyNz, GL_STATIC_DRAW);

	// normals data in location 1 (used in vertex shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Load the index data: ---------------------------------------------------------

	// Bind our 2nd VBO as being the active buffer and storing index ) 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

	// Copy the index data to our buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), pTriList, GL_STATIC_DRAW);


	delete[] pCubeData_xyz;
	delete[] pCubeData_uv;
	delete[] pCubeData_NxNyNz;
	delete[] pTriList;

}

CubeMesh::CubeMesh(const char *const pMeshFileName)
	: Mesh()
{
	assert(pMeshFileName);
	this->privCreateVAO(pMeshFileName);
}

CubeMesh::~CubeMesh()
{
	// remove anything dynamic here
}


// --- End of File ---
