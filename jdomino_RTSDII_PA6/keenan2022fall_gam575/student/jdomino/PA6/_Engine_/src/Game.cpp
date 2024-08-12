//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Game.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "ProtoMesh.h"
#include "SphereMesh.h"
#include "CubeMesh.h"
#include "Keyboard.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "CameraMan.h"
#include "CameraMesh.h"
#include "CameraDemoInput.h"
#include "GameObjectBoundingSphere.h"
#include "AnimTimer.h"
#include "Anim.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"

using namespace Azul;

namespace Azul
{
	// Todo: clean up
	AnimController *pAnimController;
	Clip *pWalkClip = nullptr;

	Clip* pDieLeftClip = nullptr;
	AnimController* pDieLeftAnimController;

	Clip* pTurnRightClip = nullptr;
	AnimController* pTurnRightController;

	Clip* pRunClip = nullptr;
	AnimController* pRunAnimController;

	Clip* pShotUpClip = nullptr;
	AnimController* pShotUpAnimController;

	Clip* pSideStepClip = nullptr;
	AnimController* pSideStepAnimController;

	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------
	Game::Game(const char *const pWindowName, const int Width, const int Height)
		:Engine(pWindowName, Width, Height), 
		pProtoVersion(nullptr)
	{
		assert(pWindowName);
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::Initialize()
	//		Allows the engine to perform any initialization it needs to before 
	//      starting to run.  This is where it can query for any required services 
	//      and load any non-graphic related content. 
	//-----------------------------------------------------------------------------
	void Game::Initialize()
	{

	}


	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	void Game::LoadContent()
	{
		// Set the Asset proto version for checking.
		this->SetProtoVersion("1.0.1");

		// Start the managers
		InputMan::Create();
		TextureMan::Create();
		MeshNodeMan::Create();
		ShaderMan::Create();
		CameraMan::Create();
		GameObjectMan::Create();

		// --------------------------
		// Camera setup
		// --------------------------

		// Camera_0		
		Camera *pCam0 = new Camera();
		pCam0->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 10000.0f);
		pCam0->setOrientAndPosition(Vec3(1.0f, 0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(-1.0f, 12.0f, 0.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent(Camera::Name::CAMERA_0);

		// -----------------------------------
		// Load the Mesh from Data file
		// -----------------------------------

		Mesh *pPyramidMesh = new ProtoMesh("PyramidMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::PYRAMID, pPyramidMesh);


		Mesh *pBone_Mesh = new ProtoMesh("Bone.m.proto.azul");
		Mesh *pBone_001_Mesh = new ProtoMesh("Bone_001.m.proto.azul");
		Mesh *pBone_L_Mesh = new ProtoMesh("Bone_L.m.proto.azul");
		Mesh *pBone_L_001_Mesh = new ProtoMesh("Bone_L_001.m.proto.azul");
		Mesh *pBone_L_002_Mesh = new ProtoMesh("Bone_L_002.m.proto.azul");
		Mesh *pBone_R_Mesh = new ProtoMesh("Bone_R.m.proto.azul");
		Mesh *pBone_R_001_Mesh = new ProtoMesh("Bone_R_001.m.proto.azul");
		Mesh *pBone_R_002_Mesh = new ProtoMesh("Bone_R_002.m.proto.azul");

		MeshNodeMan::Add(Mesh::Name::Bone,       pBone_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_001,   pBone_001_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_L,     pBone_L_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_L_001, pBone_L_001_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_L_002, pBone_L_002_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_R,     pBone_R_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_R_001, pBone_R_001_Mesh);
		MeshNodeMan::Add(Mesh::Name::Bone_R_002, pBone_R_002_Mesh);

		// ----------------------------------
		// Create/Load Shader 
		// ----------------------------------

		ShaderObject *pShaderObject_constcolor;
		pShaderObject_constcolor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constColorRender");
		assert(pShaderObject_constcolor);

		ShaderObject *pShaderObject_color;
		pShaderObject_color = ShaderMan::Add(ShaderObject::Name::COLOR_POSITION, "colorRender");
		assert(pShaderObject_color);

		ShaderObject *pShaderObject_texture;
		pShaderObject_texture = ShaderMan::Add(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender");
		assert(pShaderObject_texture);

		ShaderObject *pShaderObject_textureLight;
		pShaderObject_textureLight = ShaderMan::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
		assert(pShaderObject_textureLight);

		ShaderObject *pShaderObject_constColor;
		pShaderObject_constColor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constcolorRender");
		assert(pShaderObject_constColor);

		ShaderObject *pShaderObject_colorSingle;
		pShaderObject_colorSingle = ShaderMan::Add(ShaderObject::Name::COLOR_SINGLE, "colorSingleRender");
		assert(pShaderObject_colorSingle);

		// ------------------------------------------
		// Load Textures from Data File
		// ------------------------------------------
		TextureMan::Add("HotPink.t.proto.azul", Texture::Name::HOT_PINK);
		TextureMan::Add("Duckweed.t.proto.azul", Texture::Name::DUCKWEED);
		TextureMan::Add("Rocks.t.proto.azul", Texture::Name::ROCKS);
		TextureMan::Add("Stone.t.proto.azul", Texture::Name::STONES);
		TextureMan::Add("RedBrick.t.proto.azul", Texture::Name::RED_BRICK);
		TextureMan::Add("ChickenbotDiffuse.t.proto.azul", Texture::Name::CHICKEN_BOT);
		
		// ---------------------------------
		// Create Animation
		// ---------------------------------

		pWalkClip = new Clip(NUM_BONES, Clip::ClipType::WALK);
		assert(pWalkClip);

		pRunClip = new Clip(NUM_BONES, Clip::ClipType::RUN);
		assert(pRunClip);

		pSideStepClip = new Clip(NUM_BONES, Clip::ClipType::SIDESTEP);
		assert(pSideStepClip);

		pShotUpClip = new Clip(NUM_BONES, Clip::ClipType::SHOTUP);
		assert(pShotUpClip);

		//pTurnRightClip = new Clip(NUM_BONES, Clip::ClipType::TURNRIGHT);
		//assert(pTurnRightClip);

		pDieLeftClip = new Clip(NUM_BONES, Clip::ClipType::DIELEFT);
		assert(pDieLeftClip);



		AnimTime delta = 0.1f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pAnimController = new AnimController(delta, Skeleton::Position::CENTER, pWalkClip);
		assert(pAnimController);

		//---DIE LEFT--- // 
		AnimTime delta3 = 0.1f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pDieLeftAnimController = new AnimController(delta3, Skeleton::Position::TOPLEFT, pDieLeftClip);
		assert(pDieLeftAnimController);

		//---TURN RIGHT--- // 
		//AnimTime delta3 = 0.1f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		//pTurnRightController = new AnimController(delta3, Skeleton::Position::TOPLEFT, pTurnRightClip);
		//assert(pTurnRightController);

		//---RUN-- // 
		AnimTime delta4 = 0.3f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pRunAnimController = new AnimController(delta4, Skeleton::Position::BOTTOMLEFT, pRunClip);
		assert(pRunAnimController);

		//---Shot-- // 
		AnimTime delta5 = 0.3f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pShotUpAnimController = new AnimController(delta5, Skeleton::Position::TOPRIGHT, pShotUpClip);
		assert(pRunAnimController);

		//---SideStep-- // 		
		AnimTime delta6 = 0.3f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pSideStepAnimController = new AnimController(delta6, Skeleton::Position::BOTTOMRIGHT, pSideStepClip);
		assert(pSideStepAnimController);		

	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float )
	{
		this->intervalTimer.Toc(); 
		this->intervalTimer.Tic(); 

		// ------------------------------------
		// Camera update
		// ------------------------------------
		Camera *pCam = CameraMan::GetCurrent();
		pCam->updateCamera();

		// ------------------------------------
		// Animate Me
		// ------------------------------------
		pAnimController->Update();
		pDieLeftAnimController->Update();
		//pTurnRightController->Update();
		pRunAnimController->Update();   
		pShotUpAnimController->Update();   
		pSideStepAnimController->Update(); 

		// ------------------------------------
		// Update GameObjects
		// ------------------------------------
		GameObjectMan::Update(this->globalTimer.Toc());

		if (GetKeyState('1'))
		{
			//send die to middle
			pDieLeftAnimController->SetLocation(Skeleton::Position::CENTER);
			pAnimController->SetLocation(Skeleton::Position::TOPLEFT);

			//everything else
			pSideStepAnimController->SetLocation(Skeleton::Position::BOTTOMRIGHT);
			pShotUpAnimController->SetLocation(Skeleton::Position::TOPRIGHT);
			pRunAnimController->SetLocation(Skeleton::Position::BOTTOMLEFT);

		}

		if (GetKeyState('2'))
		{
			//send sidestep to middle
			pSideStepAnimController->SetLocation(Skeleton::Position::CENTER);
			pAnimController->SetLocation(Skeleton::Position::BOTTOMRIGHT);

			//everything else
			pDieLeftAnimController->SetLocation(Skeleton::Position::TOPLEFT);
			pShotUpAnimController->SetLocation(Skeleton::Position::TOPRIGHT);
			pRunAnimController->SetLocation(Skeleton::Position::BOTTOMLEFT);
		}

		if (GetKeyState('3'))
		{
			//send run to middle
			pRunAnimController->SetLocation(Skeleton::Position::CENTER);
			pAnimController->SetLocation(Skeleton::Position::BOTTOMLEFT);

			//everything else
			pSideStepAnimController->SetLocation(Skeleton::Position::BOTTOMRIGHT);
			pDieLeftAnimController->SetLocation(Skeleton::Position::TOPLEFT);
			pShotUpAnimController->SetLocation(Skeleton::Position::TOPRIGHT);
		}

		if (GetKeyState('4'))
		{
			//send shot to middle
			pShotUpAnimController->SetLocation(Skeleton::Position::CENTER);
			pAnimController->SetLocation(Skeleton::Position::TOPRIGHT);

			//eerything else
			pSideStepAnimController->SetLocation(Skeleton::Position::BOTTOMRIGHT);
			pDieLeftAnimController->SetLocation(Skeleton::Position::TOPLEFT);
			pRunAnimController->SetLocation(Skeleton::Position::BOTTOMLEFT);
		}

		if (GetKeyState('5'))
		{
			//send walk to center
			pAnimController->SetLocation(Skeleton::Position::CENTER);

			pSideStepAnimController->SetLocation(Skeleton::Position::BOTTOMRIGHT);
			pDieLeftAnimController->SetLocation(Skeleton::Position::TOPLEFT);
			pShotUpAnimController->SetLocation(Skeleton::Position::TOPRIGHT);
			pRunAnimController->SetLocation(Skeleton::Position::BOTTOMLEFT);
		}
	}


	//-----------------------------------------------------------------------------
	// Game::Draw()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Draw()
	{
		GameObjectMan::Draw();
	}


	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnLoadContent()
	{
		// Todo fix this - verify OpenGL removal

		//  glDeleteVertexArrays(1, &vao);
		//  glDeleteProgram(pShaderObject->programObject);
		//  glDeleteBuffers(1, &buffer);

		TextureMan::Destroy();
		InputMan::Destroy();
		GameObjectMan::Destroy();
		MeshNodeMan::Destroy();
		ShaderMan::Destroy();
		CameraMan::Destroy();

		delete pAnimController;
		delete pRunAnimController;
		delete pTurnRightController;
		delete pShotUpAnimController;
		delete pDieLeftAnimController;
		delete pSideStepAnimController;

		delete pWalkClip;
		delete pRunClip;
		delete pTurnRightClip;
		delete pShotUpClip;
		delete pDieLeftClip;
		delete pSideStepClip;
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	//------------------------------------------------------------------
	void Game::ClearBufferFunc()
	{
	#ifdef _DEBUG
		const GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	#else
		const GLfloat color[] = { 0.85f, 0.7f, 0.7f, 1.0f };
	#endif
		const GLfloat one = 1.0f;

		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, color);
		glClearBufferfv(GL_DEPTH, 0, &one);
	}


	void Game::SetProtoVersion( char * const pVersion)
	{
		assert(pVersion);

		this->pProtoVersion = pVersion;
	}

	const char *const Game::GetProtoVersion()
	{
		return this->pProtoVersion;
	}

}  // namespace 

// --- End of File ---
