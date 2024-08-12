//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Game.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "ProtoMesh.h"
#include "SphereMesh.h"
#include "CubeMesh.h"
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
#include "BoundingSphereGameObject.h"
#include "SimpleGameObject.h"
#include "AnimTimer.h"


// Todo: ----------------------------------

	// Global: make a singleton
	CameraMesh *pCameraMesh;

namespace Azul
{

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
		pCam0->setPerspective(60.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 0.10f, 1000.0f);
		pCam0->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 8.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent(Camera::Name::CAMERA_0);

		// -----------------------------------
		// Load the Mesh from Data file
		// -----------------------------------

		//MY MESHES

		//A
		Mesh* pFishMesh = new ProtoMesh("BarramundiFish.mt.proto.azul", Texture::Name::FISH);
		MeshNodeMan::Add(Mesh::Name::FISH, pFishMesh);

		//pFishMesh->poRefSphere

		//B
		Mesh* pCorsetMesh = new ProtoMesh("Corset.mt.proto.azul", Texture::Name::CORSET);
		MeshNodeMan::Add(Mesh::Name::CORSET, pCorsetMesh);

		//C
		Mesh* pOldCameraMesh = new ProtoMesh("camera.mt.proto.azul", Texture::Name::OLD_CAMERA);
		MeshNodeMan::Add(Mesh::Name::OLD_CAMERA, pOldCameraMesh);
		Mesh* pOldTripodMesh = new ProtoMesh("tripod.mt.proto.azul", Texture::Name::OLD_TRIPOD);
		MeshNodeMan::Add(Mesh::Name::OLD_TRIPOD, pOldTripodMesh);

		//D
		Mesh* pAvocadoMesh = new ProtoMesh("Avocado.mt.proto.azul", Texture::Name::AVOCADO);
		MeshNodeMan::Add(Mesh::Name::AVOCADO, pAvocadoMesh);


		Mesh *pCubeMesh = new ProtoMesh("cubeMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CUBE, pCubeMesh);

		Mesh *pSphereMesh = new ProtoMesh("SphereMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::SPHERE, pSphereMesh);

		Mesh *pCrateMesh = new ProtoMesh("Avocado.mt.proto.azul", Texture::Name::CRATE);
		MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);

		Mesh *pBoneMesh = new ProtoMesh("2Bone.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::BONE_2, pBoneMesh);

		// ----------------------------------
		// Create/Load Shader 
		// ----------------------------------

		ShaderObject *pShaderObject_constcolor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constColorRender");
		assert(pShaderObject_constcolor);

		ShaderObject *pShaderObject_color = ShaderMan::Add(ShaderObject::Name::COLOR_POSITION, "colorRender");
		assert(pShaderObject_color);

		ShaderObject *pShaderObject_texture = ShaderMan::Add(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender");
		assert(pShaderObject_texture);

		ShaderObject *pShaderObject_textureLight = ShaderMan::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
		assert(pShaderObject_textureLight);

		ShaderObject *pShaderObject_constColor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constcolorRender");
		assert(pShaderObject_constColor);

		ShaderObject *pShaderObject_colorSingle = ShaderMan::Add(ShaderObject::Name::COLOR_SINGLE, "colorSingleRender");
		assert(pShaderObject_colorSingle);

		// ------------------------------------------
			// Load Textures from Data File
			// ------------------------------------------
			TextureMan::Add("HotPink.t.proto.azul", Texture::Name::HOT_PINK);
			TextureMan::Add("Duckweed.t.proto.azul", Texture::Name::DUCKWEED);
			TextureMan::Add("Rocks.t.proto.azul", Texture::Name::ROCKS);
		//	TextureMan::Add("Stone.t.proto.azul", Texture::Name::STONES);
			TextureMan::Add("RedBrick.t.proto.azul", Texture::Name::RED_BRICK);

		// ---------------------------
		// Game Objects
		// --------------------------

			// Create GameObject
			//SimpleGameObject *pGameObj = nullptr;
			GraphicsObject *pGraphicsObj = nullptr;

			Vec4 Yellow(1.0f, 1.0f, 0.0f, 1.0f);
			Vec4 color(1.50f, 1.50f, 1.50f, 1.0f);
			Vec3 pos(1, 1, 1);

			//A
			pGraphicsObj = new GraphicsObject_TextureLight(pFishMesh, pShaderObject_textureLight, Texture::Name::FISH, color, pos);
			SimpleGameObject* pGameObjFish;
			pGameObjFish = new SimpleGameObject(pGraphicsObj);
			pGameObjFish->SetScale(2.0f, 2.0f, 2.0f);
			pGameObjFish->SetPos(-2.0f, 0.0f, 0.0f);
			pGameObjFish->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjFish);			
			
			pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			SimpleGameObject* pGameObjFishSphere;
			pGameObjFishSphere = new SimpleGameObject(pGraphicsObj);
			pGameObjFishSphere->SetScale(0.75f, 0.75f, 0.75f);
			pGameObjFishSphere->SetPos(-2.0f, 0.2f, 0.0f);
			pGameObjFishSphere->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjFishSphere);

			/*pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			BoundingSphereGameObject* pGameObjSphere;
			pGameObjSphere = new BoundingSphereGameObject(pGraphicsObj);
			pGameObjSphere->SetName("BoundingSphere_FISH");
			pGameObjSphere->SetBoundingSphereReference(pGameObjFish);			
			GameObjectMan::Add(pGameObjSphere);*/

			//B
			pGraphicsObj = new GraphicsObject_TextureLight(pCorsetMesh, pShaderObject_textureLight, Texture::Name::CORSET, color, pos);
			SimpleGameObject* pGameObjCorset;
			pGameObjCorset = new SimpleGameObject(pGraphicsObj);
			pGameObjCorset->SetScale(15.0f, 15.0f, 15.0f);
			pGameObjCorset->SetPos(0.0f, 0.0f, 0.0f);
			pGameObjCorset->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjCorset);

			pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			SimpleGameObject* pGameObjCorsetSphere;
			pGameObjCorsetSphere = new SimpleGameObject(pGraphicsObj);
			pGameObjCorsetSphere->SetScale(0.75f, 0.75f, 0.75f);
			pGameObjCorsetSphere->SetPos(0.0f, 0.45f, 0.0f);
			pGameObjCorsetSphere->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjCorsetSphere);

			//pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			//BoundingSphereGameObject* pGameObjSphere;
			//pGameObjSphere = new BoundingSphereGameObject(pGraphicsObj);
			//pGameObjSphere->SetName("BoundingSphere_CORSET");
			//pGameObjSphere->SetBoundingSphereReference(pGameObjCorset);
			//GameObjectMan::Add(pGameObjSphere);

			//C
			pGraphicsObj = new GraphicsObject_TextureLight(pOldCameraMesh, pShaderObject_textureLight, Texture::Name::OLD_CAMERA, color, pos);
			SimpleGameObject* pGameObjOldCamera;
			pGameObjOldCamera = new SimpleGameObject(pGraphicsObj);
			pGameObjOldCamera->SetScale(0.15f, 0.15f, 0.15f);
			pGameObjOldCamera->SetPos(2.0f, 0.0f, 0.0f); 
			//pGameObjOldCamera->rotY = -1.0f;
			pGameObjOldCamera->deltaRotY= 0.003f;
			GameObjectMan::Add(pGameObjOldCamera);

			pGraphicsObj = new GraphicsObject_TextureLight(pOldTripodMesh, pShaderObject_textureLight, Texture::Name::OLD_TRIPOD, color, pos);
			SimpleGameObject* pGameObjOldTripod;
			pGameObjOldTripod = new SimpleGameObject(pGraphicsObj);
			pGameObjOldTripod->SetScale(0.15f, 0.15f, 0.15f);
			pGameObjOldTripod->SetPos(2.0f, 0.0f, 0.0f);
			//pGameObjOldTripod->rotY = -1.0f;
			pGameObjOldTripod->deltaRotY = 0.003f;
			GameObjectMan::Add(pGameObjOldTripod);

			pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			SimpleGameObject* pGameObjOldCameraSphere;
			pGameObjOldCameraSphere = new SimpleGameObject(pGraphicsObj);
			pGameObjOldCameraSphere->SetScale(1.2f, 1.2f, 1.2f);
			pGameObjOldCameraSphere->SetPos(2.0f, 0.9f, 0.0f);
			pGameObjOldCameraSphere->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjOldCameraSphere);

			//pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			//BoundingSphereGameObject* pGameObjSphere;
			//pGameObjSphere = new BoundingSphereGameObject(pGraphicsObj);
			//pGameObjSphere->SetName("BoundingSphere_OLD_CAMERA");
			//pGameObjSphere->SetBoundingSphereReference(pGameObjOldTripod);
			//GameObjectMan::Add(pGameObjSphere);

			//D
			pGraphicsObj = new GraphicsObject_TextureLight(pAvocadoMesh, pShaderObject_textureLight, Texture::Name::AVOCADO, color, pos);
			SimpleGameObject* pGameObjAvocado;
			pGameObjAvocado = new SimpleGameObject(pGraphicsObj);
			pGameObjAvocado->SetScale(8.0f, 8.0f, 8.0f);
			pGameObjAvocado->SetPos(4.0f, -0.0f, 0.0f);
			pGameObjAvocado->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjAvocado);

			pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			SimpleGameObject* pGameObjAvocadoSphere;
			pGameObjAvocadoSphere = new SimpleGameObject(pGraphicsObj);
			pGameObjAvocadoSphere->SetScale(0.4f, 0.4f, 0.4f);
			pGameObjAvocadoSphere->SetPos(4.0f, 0.25f, 0.0f);
			pGameObjAvocadoSphere->deltaRotY = .003f;
			GameObjectMan::Add(pGameObjAvocadoSphere);

			//pGraphicsObj = new GraphicsObject_WireframeConstantColor(pSphereMesh, pShaderObject_colorSingle, Yellow);
			////BoundingSphereGameObject* pGameObjSphere;
			//pGameObjSphere = new BoundingSphereGameObject(pGraphicsObj);
			//pGameObjSphere->SetName("BoundingSphere_AVOCADO");
			//pGameObjSphere->SetBoundingSphereReference(pGameObjAvocado);
			//GameObjectMan::Add(pGameObjSphere);

			

			/*
			pGraphicsObj = new GraphicsObject_TextureLight(pCubeMesh, pShaderObject_textureLight, Texture::Name::DUCKWEED, color, pos);
			pGameObj = new SimpleGameObject(pGraphicsObj);
			pGameObj->SetScale(2.0f, 2.0f, 2.0f);
			pGameObj->SetPos(0.0f, 0.0f, 0.0f);
			GameObjectMan::Add(pGameObj);

			pGraphicsObj = new GraphicsObject_TextureLight(pCubeMesh, pShaderObject_textureLight, Texture::Name::STONES, color, pos);
			pGameObj = new SimpleGameObject(pGraphicsObj);
			pGameObj->SetScale(2.0f, 2.0f, 2.0f);
			pGameObj->SetPos(-2.0f, 1.70f, 0.0f);
			GameObjectMan::Add(pGameObj);

			pGraphicsObj = new GraphicsObject_TextureLight(pCrateMesh, pShaderObject_textureLight, Texture::Name::CRATE, color, pos);
			pGameObj = new SimpleGameObject(pGraphicsObj);
			pGameObj->SetScale(5.5f, 5.5f, 5.5f);
			pGameObj->SetPos(-2.0f, -0.0f, 0.0f);
			GameObjectMan::Add(pGameObj);*/

	/*		pGraphicsObj = new GraphicsObject_TextureLight(pBoneMesh, pShaderObject_textureLight, Texture::Name::RED_BRICK, color, pos);
			pGameObj = new SimpleGameObject(pGraphicsObj);
			pGameObj->SetScale(1,2,1);
			pGameObj->SetPos(0.0f, 1.0f, 0.0f);
			GameObjectMan::Add(pGameObj);*/


		Trace::out("\n");
		Trace::out("Mat4: %d \n", sizeof(Mat4));
		Trace::out("Mat3: %d \n", sizeof(Mat3));

		Trace::out("Vec4: %d \n", sizeof(Vec4));
		Trace::out("Vec3: %d \n", sizeof(Vec3));
		Trace::out("\n");

		// BUG - if there are no game objects... crash


		// Timer test ----------------------------------

		// Create a Timer.
		AnimTimer timer;

		// Mark our begin time.
		timer.Tic();

		volatile int c = 0;

		for(int i = 0; i < 1000000000; i++)
		{
			c += 1;
		}

		AnimTime elapsedTime = timer.Toc();

		int timeInSeconds_Integer = AnimTime::Quotient(elapsedTime, AnimTime(AnimTime::Duration::ONE_SECOND));
		int timeInSeconds_ms = AnimTime::Quotient(elapsedTime, AnimTime(AnimTime::Duration::ONE_MILLISECOND));

		AnimTime timeInMs_remainder = AnimTime::Remainder(elapsedTime, AnimTime(AnimTime::Duration::ONE_SECOND));
		int timeInSeconds_ms_remainder = AnimTime::Quotient(timeInMs_remainder, AnimTime(AnimTime::Duration::ONE_MILLISECOND));

		Trace::out(" time in seconds: %d \n", timeInSeconds_Integer);
		Trace::out(" time in     ms : %d \n", timeInSeconds_ms);
		Trace::out(" remainder   ms : %d \n", timeInSeconds_ms_remainder);

		AnimTime t1(AnimTime::Duration::MAX);

		volatile int minutes = (AnimTime::Quotient(t1, AnimTime(AnimTime::Duration::ONE_MINUTE)));

		Trace::out(" minutes: %d  or  hours %d\n", minutes, minutes / 60);


		// Timer test ----------------------------------

	}


	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------

	void Game::Update(float currentTime)
	{
		// Mark our end time.
		this->intervalTimer.Toc();

			// Update camera - make sure everything is consistent
			Camera *pCam = CameraMan::GetCurrent();
			pCam->updateCamera();


			if (GetKeyState('1'))
			{
				
			}

			// update objects
			GameObjectMan::Update(this->globalTimer.Toc());

			static int i = 0;

			Trace::out("%d: %f\n", i++, currentTime);

			AnimTime elapsedTime = this->intervalTimer.Toc();

			int timeInSeconds_ms = AnimTime::Quotient(elapsedTime, AnimTime(AnimTime::Duration::ONE_MILLISECOND));

			AnimTime timeInMs_remainder = AnimTime::Remainder(elapsedTime, AnimTime(AnimTime::Duration::ONE_MILLISECOND));
			int timeInSeconds_us_remainder = AnimTime::Quotient(timeInMs_remainder, AnimTime(AnimTime::Duration::ONE_MICROSECOND));

			Trace::out(" time in     ms : %d \n", timeInSeconds_ms);
			Trace::out(" remainder   us : %d \n", timeInSeconds_us_remainder);

		// Mark our begin time.
		this->intervalTimer.Tic();
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
