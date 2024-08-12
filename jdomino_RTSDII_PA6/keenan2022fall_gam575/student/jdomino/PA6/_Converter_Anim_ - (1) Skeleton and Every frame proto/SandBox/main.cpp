//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


// -------------------------
// Anim Converter 3
// -------------------------


#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "ChickenBot.h"
#include "CreateTexture.h"
#include "GLTF.h"
#include "StringThis.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"
#include "ShaderLayout.h"
#include "MathEngine.h"
#include "Skeleton.h"
#include "Anim.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;


int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Create custom models/texture into proto format
	// Need to be converted each time the format changes
	CreateCubeMesh();
	CreatePyramidMesh();
	CreateSphereMesh();
	CreateTextureTGA("HotPink.tga");
	CreateTextureTGA("Rocks.tga");
	CreateTextureTGA("Duckweed.tga");
	CreateTextureTGA("RedBrick.tga");
	CreateTextureTGA("Stone.tga");
	CreateTexturePNG("ChickenbotDiffuse.png");  //<--- use this for the model
	CreateChickenBotModels();


	bool status;
	tinygltf::Model gltfModel;

	// runtime model
	meshData  runModel;

	// glb file name defined here:
	const char *pGLB_Name = "turn_right+mesh";
	const char *pGLB_extension = ".glb";
	const char *pProto_extension = ".proto.azul";

	size_t FileNameSize = strlen(pGLB_Name) + strlen(pGLB_extension) + 1;

	char *poFileName = new char[FileNameSize]();
	strcat_s(poFileName, FileNameSize, pGLB_Name);
	strcat_s(poFileName, FileNameSize, pGLB_extension);

	size_t ProtoFileNameSize = strlen(pGLB_Name) + strlen(pProto_extension) + 1;

	char *poProtoFileName = new char[ProtoFileNameSize]();
	strcat_s(poProtoFileName, ProtoFileNameSize, pGLB_Name);
	strcat_s(poProtoFileName, ProtoFileNameSize, pProto_extension);

	// Load the gltfModel
	status = GLTF::LoadBinary(gltfModel, poFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char *poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, poFileName);
	assert(status);

	// Get GLB_Header
	GLB_header glbHeader;
	status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
	assert(status);

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



	// SKELETON
	SKEL skelData;
	skelData.CreateVector(gltfModel);
	Trace::out("\n");
	Trace::out("\n");

	// ANIMATION
	ANIM animData;
	animData.CreateAnim(gltfModel);
	Trace::out("\n");
	Trace::out("\n");


	//-------------------------------------------------
	// Fill out the runtime Model data
	//-------------------------------------------------


	//---------------------------------
	// Model Name
	//---------------------------------
	memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.nodes[1].name.c_str(), gltfModel.nodes[1].name.length());

	//---------------------------------
	// Set vbo 
	//---------------------------------
	//GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_VERT, "POSITION", runModel.vbo_vert, pBinaryBuff);
	//runModel.vbo_vert.Print("vbo_vert");

	//GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_NORM, "NORMAL", runModel.vbo_norm, pBinaryBuff);
	//runModel.vbo_norm.Print("vbo_norm");

	//GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_TEXT, "TEXCOORD_0", runModel.vbo_uv, pBinaryBuff);
	//runModel.vbo_uv.Print("vbo_uv");

	//GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_COLOR, "COLOR_0", runModel.vbo_color, pBinaryBuff);
	//runModel.vbo_color.Print("vbo_color");

	//GLTF::SetVBO_index(gltfModel, ATTRIB_LOCATION_INDEX, runModel.vbo_index, pBinaryBuff);
	//runModel.vbo_index.Print("vbo_index");


	//--------------------------------
	// PolyCount
	//--------------------------------
	runModel.triCount = runModel.vbo_index.count / 3;
	runModel.vertCount = runModel.vbo_vert.count;

	//--------------------------------
	// RenderMode
	//--------------------------------
	runModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
	assert(runModel.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	// Set texture from Image vector

	// Find index to color
	if(gltfModel.images.size() > 0)
	{
		unsigned int colorIndex = 0;
		colorIndex = (unsigned int)gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;

		GLTF::SetTexture(gltfModel, colorIndex, runModel.text_color, pBinaryBuff);
		//runModel.text_color.Print("text_color");
	}

	delete[] poBuff;

	//Trace::out("--------------\n");
	//Trace::out("--------------\n");
	//Trace::out("--------------\n");

	//runModel.Print("mA");
	meshData_proto mA_proto;
	runModel.Serialize(mA_proto);

	//Trace::out("\n");
	//Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	//Trace::out("\n");


	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	const char *pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	// Create output name
	std::string BaseName(pGLB_Name);
	std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
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

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
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

	//Trace::out("--------------\n");
	//Trace::out("--------------\n");
	//Trace::out("--------------\n");

	std::string strIn(poNewBuff, FileLength);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);
	//mB.Print("mB");

	delete[] poProtoFileName;
	delete[] poFileName;
	delete[] poJSON;
	delete[] poNewBuff;

	google::protobuf::ShutdownProtobufLibrary();

	system("copy *.azul .\\..\\Data");
	system("del *.azul");

	return 0;

}

// ---  End of File ---------------
