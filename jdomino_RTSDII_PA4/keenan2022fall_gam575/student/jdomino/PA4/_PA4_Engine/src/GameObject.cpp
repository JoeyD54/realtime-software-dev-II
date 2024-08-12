//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"

namespace Azul
{

	GameObject::GameObject(GraphicsObject *pGraphicsObject)
		: poGraphicsObject(pGraphicsObject)
	{
		this->poWorld = new Mat4(Mat4::Special::Identity);
		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		assert(poWorld);
		assert(poTrans);
		assert(poScale);
		assert(pGraphicsObject);

		this->rotY = 0.0f;
		this->rotZ = 0.0f;
		this->deltaRot = 0.0f;
	}

	GameObject::~GameObject()
	{
		delete this->poWorld;
		delete this->poTrans;
		delete this->poScale;
		delete this->poGraphicsObject;

	}

	Mat4 *GameObject::GetWorld()
	{
		return this->poWorld;
	}

	GraphicsObject *GameObject::GetGraphicsObject()
	{
		return this->poGraphicsObject;
	}

	void GameObject::privUpdate(float currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		this->rotY += deltaRot;
		this->rotZ += 0.0f;// 0.01f;

		Mat4 Scale(Mat4::Scale::XYZ, *this->poScale);
		Mat4 TransA(Mat4::Trans::XYZ, *this->poTrans);
		Mat4 RotY(Mat4::Rot1::Y, this->rotY);
		Mat4 RotZ(Mat4::Rot1::Z, this->rotZ);

		// world matrix
		*this->poWorld = Scale * RotY * RotZ * TransA;
	}

	void GameObject::Update(float currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void GameObject::SetWorld(Mat4 *pWorld)
	{
		assert(pWorld);
		*this->poWorld = *pWorld;
	}

	void GameObject::SetPos(const Vec3 &pos)
	{
		*this->poTrans = pos;
	}

	void GameObject::SetScale(const Vec3 &inScale)
	{
		// deep copy
		*this->poScale = inScale;
	}

	void GameObject::SetDeltaRot(float delta)
	{
		this->deltaRot = delta;
	}

	void GameObject::Draw()
	{
		GraphicsObject *pGraphicsObj = this->GetGraphicsObject();
		assert(pGraphicsObj);

		pGraphicsObj->Render();
	}

}

// --- End of File ---
