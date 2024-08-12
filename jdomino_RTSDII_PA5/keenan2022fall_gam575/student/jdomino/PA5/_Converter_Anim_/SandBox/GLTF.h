//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GLTF_H
#define GLTF_H

#include "tiny_gltf.h"
using namespace tinygltf;

#include "meshData.h"

struct GLB_header
{
	uint32_t magic;
	uint32_t version;
	uint32_t length;
};

struct CHUNK_header
{
	uint32_t chunkLength;
	uint32_t chunkType;
	unsigned char chunkData[];
};

class GLTF
{
public:

	static bool LoadBinary(Model &model, const char *const pFileName);
	static bool LoadASCII(Model &model, const char *const pFileName);

	static bool GetGLBRawBuffer(char *&pBuff, unsigned int &BuffSize, const char *const pFileName);
	static bool GetGLBHeader(GLB_header &header, const char *const pBuff, unsigned int BuffSize);
	static bool GetRawJSON(char *&pJSON, unsigned int &JsonSize, const char *const pBuff, unsigned int BuffSize);
	static bool GetBinaryBuffPtr(char *&pBinaryBuff, unsigned int &BinaryBuffSize, const char *const pBuff, unsigned int BuffSize);

	static bool SetCustomVBO(   unsigned int AttribIndex, 
								const char *pKey,
								vboData &vbo,
								void *data,
								unsigned int sizeInBytes,
								unsigned int count,
								vboData::VBO_COMPONENT componentType,
								vboData::VBO_TYPE type,
								vboData::VBO_TARGET target);

	static bool SetCustomVBO_index( unsigned int AttribIndex,
									const char *pKey,
									vboData &vbo,
									void *data,
									unsigned int sizeInBytes,
									unsigned int count,
									vboData::VBO_COMPONENT componentType,
									vboData::VBO_TYPE type,
									vboData::VBO_TARGET target);

	static bool SetVBO(Model &gltfModel, unsigned int AttribIndex, const char *pKey, vboData &vbo, char *pBinaryBuff, unsigned int meshIndex = 0);
	static bool SetVBO_index(Model &gltfModel, unsigned int AttribIndex, vboData &vbo, char *pBinaryBuff, unsigned int meshIndex = 0);
	static bool SetTexture(Model &gltfModel, unsigned int index, textureData &text,char *pBinaryBuff);

	static void PrintData(char *pBinaryBuff, size_t byteOffset, size_t count, vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE vboType);

	static bool GetAzulProtoType(const char *&pProtoFileType, meshData &_meshData);
};

#endif

// --- End of File ---
