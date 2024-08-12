//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "GLTF_Helper.h"
#include "meshData.h"
#include "json.hpp"
#include "File.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	bool status;
	tinygltf::Model gltfModel;

	// runtime model
	meshData  runModel;

	// glb file name defined here:
	const char *pFileName = "space_frigate.glb";

	// Load the gltfModel
	status = GLTF::Load(gltfModel, pFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char *poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, pFileName);
	assert(status);

	// Get GLB_Header
	GLB_header glbHeader;
	status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
	assert(status);

	Trace::out("GLB Header:\n");
	Trace::out("\tmagic: 0x%x\n", glbHeader.magic);
	Trace::out("\tversion: 0x%x\n", glbHeader.version);
	Trace::out("\tlength: 0x%08x %d\n", glbHeader.length, glbHeader.length);
	Trace::out("\n");

	// Get Raw JSON
	char *poJSON = nullptr;
	unsigned int JsonSize(0);
	status = GLTF::GetRawJSON(poJSON, JsonSize, poBuff, BuffSize);
	assert(status);

	// Get the Binary Buffer Address
	char *pBinaryBuff = nullptr;
	unsigned int BinaryBuffSize = 0;
	status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
	assert(status);

	// Fill out the runtime Model data
	
	// Model Name
	memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.materials[0].name.c_str(), gltfModel.materials[0].name.length());
	
	// Set vbo - todo make vbo an array
	GLTF::SetVBO(gltfModel, 0, runModel.vbo_vert, pBinaryBuff);
	runModel.vbo_vert.Print("vbo_vert");

	GLTF::SetVBO(gltfModel, 1, runModel.vbo_norm, pBinaryBuff);
	runModel.vbo_norm.Print("vbo_norm");

	GLTF::SetVBO(gltfModel, 2, runModel.vbo_uv, pBinaryBuff);
	runModel.vbo_uv.Print("vbo_uv");

	GLTF::SetVBO_index(gltfModel, 3, runModel.vbo_index, pBinaryBuff);
	runModel.vbo_index.Print("vbo_index");

	// PolyCount
	runModel.triCount = runModel.vbo_index.count / 3;
	runModel.vertCount = runModel.vbo_vert.count;

	// RenderMode
	runModel.mode = meshData::GetMode(gltfModel.meshes[0].primitives[0].mode);

	// Set texture from Image vector
	// Find index to color
	unsigned int colorIndex = 0;
	colorIndex = (unsigned int )gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;
	GLTF::SetTexture(gltfModel, colorIndex, runModel.text_color, pBinaryBuff);
	runModel.text_color.Print("text_color");

	delete[] poBuff;

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	runModel.Print("mA");
	meshData_proto mA_proto;
	runModel.Serialize(mA_proto);

	Trace::out("\n");
	Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	Trace::out("\n");


	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	err = File::Open(fh, "space_frigate.proto.azul", File::Mode::WRITE);
	assert(err == File::Error::SUCCESS);

	std::string strOut;
	mA_proto.SerializeToString(&strOut);

	File::Write(fh, strOut.data(), strOut.length());
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	// -------------------------------
	// Read and recreate model data
	// -------------------------------

	err = File::Open(fh, "space_frigate.proto.azul", File::Mode::READ);
	assert(err == File::Error::SUCCESS);

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

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	std::string strIn(poNewBuff, FileLength);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);
	mB.Print("mB");
	delete[] poJSON;

	delete[] poNewBuff;

	google::protobuf::ShutdownProtobufLibrary();

	system("copy *.azul .\\..\\Data\\.");

    return 0;
}

// ---  End of File ---------------
