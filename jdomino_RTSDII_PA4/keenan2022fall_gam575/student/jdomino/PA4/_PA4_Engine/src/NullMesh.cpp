//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "NullMesh.h"


NullMesh::NullMesh(const char* const pMeshFileName)
	: Mesh()
{
	AZUL_UNUSED_VAR(pMeshFileName);
}

NullMesh::NullMesh()
	: Mesh()
{
}

NullMesh::~NullMesh()
{
	// remove anything dynamic here
}

void NullMesh::privCreateVAO(const char *const pMeshFileName)
{
	AZUL_UNUSED_VAR(pMeshFileName);
}


// --- End of File ---
