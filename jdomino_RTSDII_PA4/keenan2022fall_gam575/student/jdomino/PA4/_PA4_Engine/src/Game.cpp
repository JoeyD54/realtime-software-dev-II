//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Game.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "ProtoMesh.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"

using namespace Azul;

// Todo: ----------------------------------

// Get rid of globals
Camera *pCam = nullptr;

// Demo
	Vec3 Orig_up;
	Vec3 Orig_tar;
	Vec3 Orig_pos;
	Vec3 Orig_upNorm;
	Vec3 Orig_forwardNorm;
	Vec3 Orig_RightNorm;

//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char *const pWindowName, const int Width, const int Height)
	:Engine(pWindowName, Width, Height)
{
	assert(pWindowName);
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
	// Start the managers
	InputMan::Create();
	TextureMan::Create();
	MeshNodeMan::Create();
	ShaderMan::Create();

	// Camera setup
	pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 4.5f));
	pCam->updateCamera();

	// Load the Mesh
	Mesh *pCrateMesh(nullptr);
	Texture *pTexture(nullptr);

	// loads the mesh and returns the texture
	pCrateMesh = new ProtoMesh("space_frigate.proto.azul", pTexture);
	assert(pCrateMesh);

	MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);
	TextureMan::Add(Texture::Name::CRATE, pTexture);

	// Create/Load Shader 
	ShaderObject *pShaderObject_color;
	pShaderObject_color = ShaderMan::Add(ShaderObject::Name::COLOR_POSITION, "colorRender");
	assert(pShaderObject_color);

	ShaderObject *pShaderObject_texture = ShaderMan::Add(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender");
	assert(pShaderObject_texture);

	ShaderObject *pShaderObject_textureLight;
	pShaderObject_textureLight = ShaderMan::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(pShaderObject_textureLight);

	ShaderObject *pShaderObject_constColor;
	pShaderObject_constColor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constcolorRender");
	assert(pShaderObject_constColor);

	// Textures
	TextureMan::Add("Rocks.tga", Texture::Name::ROCKS);
	TextureMan::Add("Stone.tga", Texture::Name::STONES);
	TextureMan::Add("RedBrick.tga", Texture::Name::RED_BRICK);
	TextureMan::Add("Duckweed.tga", Texture::Name::DUCKWEED);


	// Create GameObject
	GameObject *pGameObj = nullptr;
	GraphicsObject *pGraphicsObj = nullptr;

	// Middle Row
	//pGraphicsObj = new GraphicsObject_FlatTexture(pCrateMesh, pShaderObject_texture, Texture::Name::CRATE);

	Vec4 vLightColor(1.0f, 1.0f, 1.0f, 1.0f);
	Vec3 vLightPos(1.0f, 1.0f, 0.0f);

	pGraphicsObj = new GraphicsObject_TextureLight(pCrateMesh, 
												pShaderObject_textureLight, 
												Texture::Name::CRATE,
												vLightColor, 
												vLightPos);
	pGameObj = new GameObject(pGraphicsObj);
	pGameObj->SetScale(Vec3(0.05f,0.05f,0.05f));
	pGameObj->SetPos(Vec3(0.0f, 0.0f, 0.0f));
	pGameObj->SetDeltaRot(0.003f);
	GameObjectMan::Add(pGameObj);


	// squirrel for reset
	pCam->updateCamera();
	pCam->GetHelper(Orig_up, Orig_tar, Orig_pos, Orig_upNorm, Orig_forwardNorm, Orig_RightNorm);

	Trace::out("Z, I,O,  R,G \n");

}


//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

Vec3 obj(0.0f, 0.0f, 0.0f);

void Game::Update(float currentTime)
{
	Keyboard* pKey = InputMan::GetKeyboard();


	if (pKey->GetKeyState(Keyboard::KEY_Z))
	{
		// Reset	
		obj.set(0, 0, 0);
		pCam->SetHelper(Orig_up, Orig_tar, Orig_pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_I))
	{

		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//	tar = obj;

		pos = pos + 0.03f * forwardNorm;
		//tar = tar + 0.03f * forwardNorm;
		up = up + 0.03f * forwardNorm;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_O))
	{

		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//tar = obj;

		pos = pos - 0.03f * forwardNorm;
		up = up - 0.03f * forwardNorm;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_P))
	{
		Vec3 newObj(-2, 0, 0);
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);


		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		Vec3 delta = newObj - obj;

		up += delta;
		tar += delta;
		pos += delta;

		obj = newObj;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_R))
	{
		Vec3 newObj(2, 0, 0);
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);


		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		
		Vec3 delta = newObj - obj;

		up += delta;
		tar += delta;
		pos += delta;

		obj = newObj;
		
		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_G))
	{

		Vec3 newObj(0, 0, 0);
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		Vec3 delta = newObj - obj;

		up += delta;
		tar += delta;
		pos += delta;

		obj = newObj;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_RIGHT))
	{

		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
	//	tar = obj;

		Mat4 Trans(Mat4::Trans::XYZ, tar);
		Mat4 NegTrans(Mat4::Trans::XYZ, -tar);

		Mat4 Rot;
		Rot.set(Mat4::Rot::AxisAngle, upNorm, +0.03f);

		Mat4 M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_LEFT))
	{

		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

	//	tar = obj;

		Mat4 Trans(Mat4::Trans::XYZ, tar);
		Mat4 NegTrans(Mat4::Trans::XYZ, -tar);

		Mat4 Rot;
		Rot.set(Mat4::Rot::AxisAngle, upNorm, -0.03f);

		Mat4 M = NegTrans * Rot * Trans;

		up  = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_DOWN))
	{
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

	//	tar = obj;
	

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		Mat4 Trans(Mat4::Trans::XYZ, tar);
		Mat4 NegTrans(Mat4::Trans::XYZ, -tar);
		Mat4 Rot;
		Rot.set(Mat4::Rot::AxisAngle, rightNorm, 0.03f);

		Mat4 M = NegTrans * Rot * Trans;

		up =  up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}

	if (pKey->GetKeyState(Keyboard::KEY_ARROW_UP))
	{
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		pCam->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//tar = obj;

		Mat4 Trans(Mat4::Trans::XYZ, tar);
		Mat4 NegTrans(Mat4::Trans::XYZ, -tar);
		Mat4 Rot;
		Rot.set(Mat4::Rot::AxisAngle, rightNorm, -0.03f);

		Mat4 M = NegTrans * Rot * Trans;

		up =  up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->SetHelper(up, tar, pos);
	}


	// Needs to be updated once a frame
	pCam->updateCamera();

	// Update the game objects
	GameObjectMan::Update(currentTime);
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

	delete pCam;
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


// --- End of File ---
