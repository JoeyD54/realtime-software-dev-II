//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Verify.h"

void Verify::GetVertsCopy(unsigned char *&p, unsigned int &numBytes)
{
	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	unsigned char* pBuff = new unsigned char[mB.vbo_vert.dataSize]();
	memcpy(pBuff, mB.vbo_vert.poData, mB.vbo_vert.dataSize);
	p = pBuff;
	numBytes = mB.vbo_vert.dataSize;
}

void Verify::GetNormsCopy(unsigned char *&p, unsigned int &numBytes)
{
	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	unsigned char* pBuff = new unsigned char[mB.vbo_norm.dataSize]();
	memcpy(pBuff, mB.vbo_norm.poData, mB.vbo_norm.dataSize);
	p = pBuff;
	numBytes = mB.vbo_norm.dataSize;
}

void Verify::GetUVsCopy(unsigned char *&p, unsigned int &numBytes)
{
	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	unsigned char* pBuff = new unsigned char[mB.vbo_uv.dataSize]();
	memcpy(pBuff, mB.vbo_uv.poData, mB.vbo_uv.dataSize);
	p = pBuff;
	numBytes = mB.vbo_uv.dataSize;
}

void Verify::GetIndexCopy(unsigned char *&p, unsigned int &numBytes)
{	
	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	unsigned char* pBuff = new unsigned char[mB.vbo_index.dataSize]();
	memcpy(pBuff, mB.vbo_index.poData, mB.vbo_index.dataSize);
	p = pBuff;
	numBytes = mB.vbo_index.dataSize;
}

void Verify::GetTextureBufferCopy(unsigned char *&p, unsigned int &numBytes)
{
	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	unsigned char* pBuff = new unsigned char[mB.text_color.dataSize]();
	memcpy(pBuff, mB.text_color.poData, mB.text_color.dataSize);
	p = pBuff;
	numBytes = mB.text_color.dataSize;
}


Verify::Model_stats Verify::GetModelStats()
{
	Model_stats stats;
	stats = {0};

	meshData_proto mB_proto = GetMB();

	meshData mB;
	mB.Deserialize(mB_proto);

	// General stuff
	assert(mB.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	stats.numTris = mB.triCount;
	stats.numVerts = mB.vertCount;
	stats.TextureHeight = mB.text_color.height;
	stats.TextureWidth = mB.text_color.width;

	mB.Serialize(mB_proto);

	return stats;
}

meshData_proto Verify::GetMB()
{
	// File stuff
	File::Handle fh;
	File::Error  ferror;
	MeshFileHdr meshHdr;

	ferror = File::Open(fh, "Data\\space_frigate.proto.azul", File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Get the size
	ferror = File::Seek(fh, File::Position::END, 0);
	assert(ferror == File::Error::SUCCESS);
	DWORD length;
	ferror = File::Tell(fh, length);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);
	char* poBuff = new char[length];
	assert(poBuff);
	ferror = File::Read(fh, poBuff, length);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	std::string strIn(poBuff, length);
	meshData_proto mB_proto;
	mB_proto.ParseFromString(strIn);

	delete[] poBuff;

	return mB_proto;
}


// --- End of File ---
