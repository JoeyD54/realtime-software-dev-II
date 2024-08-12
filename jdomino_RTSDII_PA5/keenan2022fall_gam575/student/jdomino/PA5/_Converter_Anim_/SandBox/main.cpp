//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CubeMesh.h"
#include "SphereMesh.h"
#include "CreateTexture.h"
#include "GLTF.h"
#include "StringThis.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"
#include "ShaderLayout.h"
#include "Vec3.h"



using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;


enum CameraMM
{
	TRIPOD,
	CAMERA
};

//Split up model creation so I can use it for more than one GLB

void CreateModel(const char* modelName)
{

	bool status;
	tinygltf::Model gltfModel;

	// runtime model
	meshData  runModel;

	const char* pGLB_extension = ".glb";
	const char* pProto_extension = ".proto.azul";

	size_t FileNameSize = strlen(modelName) + strlen(pGLB_extension) + 1;

	char* poFileName = new char[FileNameSize]();
	strcat_s(poFileName, FileNameSize, modelName);
	strcat_s(poFileName, FileNameSize, pGLB_extension);

	size_t ProtoFileNameSize = strlen(modelName) + strlen(pProto_extension) + 1;

	char* poProtoFileName = new char[ProtoFileNameSize]();
	strcat_s(poProtoFileName, ProtoFileNameSize, modelName);
	strcat_s(poProtoFileName, ProtoFileNameSize, pProto_extension);

	// Load the gltfModel
	status = GLTF::LoadBinary(gltfModel, poFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char* poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, poFileName);
	assert(status);

	// Get GLB_Header
	GLB_header glbHeader;
	status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
	assert(status);

	// Get Raw JSON
	char* poJSON = nullptr;
	unsigned int JsonSize(0);
	status = GLTF::GetRawJSON(poJSON, JsonSize, poBuff, BuffSize);
	assert(status);

	// Get the Binary Buffer Address
	char* pBinaryBuff = nullptr;
	unsigned int BinaryBuffSize = 0;
	status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
	assert(status);
	

	//---------------------------------
	// Model Name
	//---------------------------------
	memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.nodes[0].name.c_str(), gltfModel.nodes[0].name.length());

	//---------------------------------
	// Set vbo 
	//---------------------------------
	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_VERT, "POSITION", runModel.vbo_vert, pBinaryBuff);
	runModel.vbo_vert.Print("vbo_vert");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_NORM, "NORMAL", runModel.vbo_norm, pBinaryBuff);
	runModel.vbo_norm.Print("vbo_norm");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_TEXT, "TEXCOORD_0", runModel.vbo_uv, pBinaryBuff);
	runModel.vbo_uv.Print("vbo_uv");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_COLOR, "COLOR_0", runModel.vbo_color, pBinaryBuff);
	runModel.vbo_color.Print("vbo_color");

	GLTF::SetVBO_index(gltfModel, ATTRIB_LOCATION_INDEX, runModel.vbo_index, pBinaryBuff);
	runModel.vbo_index.Print("vbo_index");


	//--------------------------------
	// PolyCount
	//--------------------------------
	runModel.triCount = runModel.vbo_index.count / 3;
	runModel.vertCount = runModel.vbo_vert.count;

	//--------------------------------
	// BoundingSphere
	//--------------------------------

	//runModel.

	//Vec3* pVerts = new Vec3[(unsigned int)runModel.vertCount];
	//for (int i = 0; i < runModel.vertCount; i++)
	//{
		//pVerts[i].set(cubeData_xyz[i].x, cubeData_xyz[i].y, cubeData_xyz[i].z);
		//Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
	//}


	//--------------------------------
	// RenderMode
	//--------------------------------
	runModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
	assert(runModel.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	// Set texture from Image vector

	// Find index to color
	if (gltfModel.images.size() > 0)
	{
		unsigned int colorIndex = 0;
		colorIndex = (unsigned int)gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;

		GLTF::SetTexture(gltfModel, colorIndex, runModel.text_color, pBinaryBuff);
		runModel.text_color.Print("text_color");
	}

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

	const char* pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	// Create output name
	std::string BaseName(modelName);
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

	char* poNewBuff = new char[FileLength]();
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

	delete[] poProtoFileName;
	delete[] poFileName;
	delete[] poJSON;
	delete[] poNewBuff;
}

void CreateProtoFile(tinygltf::Model gltfModel, char* pBinaryBuff, CameraMM cameraPart)
{
	bool status;

	// runtime model
	meshData  modelName;


	if (cameraPart == CameraMM::CAMERA)
	{
		memcpy_s(modelName.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.nodes[0].name.c_str(), gltfModel.nodes[0].name.length());
	}
	else
	{
		memcpy_s(modelName.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.nodes[1].name.c_str(), gltfModel.nodes[1].name.length());
	}
	

	//---------------------------------
	// Set vbo 
	//---------------------------------
	unsigned int index = 1;
	if (cameraPart == CameraMM::TRIPOD)
	{
		index = 0;
	}
	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_VERT, "POSITION", modelName.vbo_vert, pBinaryBuff, index);
	modelName.vbo_vert.Print("vbo_vert");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_NORM, "NORMAL", modelName.vbo_norm, pBinaryBuff, index);
	modelName.vbo_norm.Print("vbo_norm");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_TEXT, "TEXCOORD_0", modelName.vbo_uv, pBinaryBuff, index);
	modelName.vbo_uv.Print("vbo_uv");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_COLOR, "COLOR_0", modelName.vbo_color, pBinaryBuff, index);
	modelName.vbo_color.Print("vbo_color");

	GLTF::SetVBO_index(gltfModel, ATTRIB_LOCATION_INDEX, modelName.vbo_index, pBinaryBuff, index);
	modelName.vbo_index.Print("vbo_index");

	//--------------------------------
	// PolyCount
	//--------------------------------
	modelName.triCount = modelName.vbo_index.count / 3;
	modelName.vertCount = modelName.vbo_vert.count;

	//--------------------------------
	// BoundingSphere
	//--------------------------------



	//--------------------------------
	// RenderMode
	//--------------------------------
	if (cameraPart == CameraMM::CAMERA)
	{
		modelName.mode = meshDataConverter::GetMode(gltfModel.meshes[1].primitives[0].mode);
	}
	else
	{
		modelName.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
	}
	
	assert(modelName.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	// Set texture from Image vector

	// Find index to color
	if (gltfModel.images.size() > 0)
	{
		unsigned int colorIndex = 0;
		if (cameraPart == CameraMM::CAMERA)
		{
			colorIndex = (unsigned int)gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;
		}
		else
		{
			colorIndex = (unsigned int)gltfModel.materials[1].pbrMetallicRoughness.baseColorTexture.index;
		}
		

		GLTF::SetTexture(gltfModel, colorIndex, modelName.text_color, pBinaryBuff);
		modelName.text_color.Print("text_color");
	}

	//---------------------------------
	// Store Model
	//---------------------------------

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	modelName.Print("mA");
	meshData_proto mA_proto;
	modelName.Serialize(mA_proto);

	Trace::out("\n");
	Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	Trace::out("\n");


	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	const char* pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, modelName);
	assert(status);

	// Create output name
	std::string BaseName(modelName.pMeshName);
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

	char* poNewBuff = new char[FileLength]();
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

	delete[] poNewBuff;
}

void CreateMultiMeshModel(const char* modelName)
{
	bool status;
	tinygltf::Model gltfModel;

	const char* pGLB_extension = ".glb";
	const char* pProto_extension = ".proto.azul";

	size_t FileNameSize = strlen(modelName) + strlen(pGLB_extension) + 1;

	char* poFileName = new char[FileNameSize]();
	strcat_s(poFileName, FileNameSize, modelName);
	strcat_s(poFileName, FileNameSize, pGLB_extension);

	size_t ProtoFileNameSize = strlen(modelName) + strlen(pProto_extension) + 1;

	char* poProtoFileName = new char[ProtoFileNameSize]();
	strcat_s(poProtoFileName, ProtoFileNameSize, modelName);
	strcat_s(poProtoFileName, ProtoFileNameSize, pProto_extension);

	// Load the gltfModel
	status = GLTF::LoadBinary(gltfModel, poFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char* poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, poFileName);
	assert(status);

	// Get GLB_Header
	GLB_header glbHeader;
	status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
	assert(status);

	// Get Raw JSON
	char* poJSON = nullptr;
	unsigned int JsonSize(0);
	status = GLTF::GetRawJSON(poJSON, JsonSize, poBuff, BuffSize);
	assert(status);

	// Get the Binary Buffer Address
	char* pBinaryBuff = nullptr;
	unsigned int BinaryBuffSize = 0;
	status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
	assert(status);


	//We now have to load up two different models.

	CreateProtoFile(gltfModel, pBinaryBuff, CameraMM::CAMERA);
	CreateProtoFile(gltfModel, pBinaryBuff, CameraMM::TRIPOD);

	delete[] poBuff;
	delete[] poProtoFileName;
	delete[] poFileName;
	delete[] poJSON;
}

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Create custom models/texture into proto format
	// Need to be converted each time the format changes
	CreateCubeMesh();
	CreateSphereMesh();
	CreateTexture("HotPink.tga");
	CreateTexture("Rocks.tga");
	CreateTexture("Duckweed.tga");
	CreateTexture("RedBrick.tga");
	CreateTexture("Stone.tga");

	CreateModel("wooden crate");
	CreateModel("2Bone");

	//A: Low Poly Model
	CreateModel("BarramundiFish");

	//B: High Poly Model
	CreateModel("Corset");

	//C: MultiMesh Model
	CreateMultiMeshModel("AntiqueCamera");

	//D: Student model
	CreateModel("Avocado");
	

	system("copy *.azul .\\..\\Data");
	system("del *.azul");

	google::protobuf::ShutdownProtobufLibrary();

    return 0;
}



// ---  End of File ---------------
