//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"

struct Vert_xyz
{
	float x;
	float y;
	float z;
};

struct Vert_NxNyNz
{
	float nx;
	float ny;
	float nz;
};

struct Vert_uv
{
	float u;
	float v;
};

struct Tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};


class Mesh
{
public:
	enum class Name
	{
		CUBE,
		PYRAMID,
		CRATE,
		NULL_MESH,
		NOT_INITIALIZED
	};

public:
	Mesh();
	Mesh(Mesh &copyMesh) = delete;
	Mesh &operator = (Mesh &copyMesh) = delete;
	virtual ~Mesh();

	// Data
	int numVerts;
	int numTris;

	GLuint vao;
	GLuint vbo_verts;  // x,y,z
	GLuint vbo_norms;  // nx,ny,nz
	GLuint vbo_texts;  // u,v
	GLuint vbo_index;  // trilist

	void Wash();
	bool Compare(DLink *pTarget);
	char *GetName();
	void SetName(Mesh::Name _name);

protected:



public:
	Name name;

};

#endif

// --- End of File ---
