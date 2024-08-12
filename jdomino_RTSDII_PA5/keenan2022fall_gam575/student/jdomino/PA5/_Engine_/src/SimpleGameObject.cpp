//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "SimpleGameObject.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Mesh.h"

namespace Azul
{
	SimpleGameObject::SimpleGameObject(GraphicsObject *pGraphicsObject)
		: GameObject(pGraphicsObject)
	{
		assert(pGraphicsObject);
		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		assert(this->poTrans);
		assert(this->poScale);

		this->rotY = 0.0f;
		this->rotZ = 0.0f;
		this->deltaRotZ = 0.0f;
		this->deltaRotY = 0.000f;
	}

	SimpleGameObject::~SimpleGameObject()
	{
		delete this->poTrans;
		delete this->poScale;
	}

	void SimpleGameObject::setMove(MoveDir move)
	{
		this->moveDir = move;
	};

	void SimpleGameObject::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		float delta = 0.01f;

		static float dirX = 1.0f;
		static float dirY = 1.0f;
		static float dirZ = 1.0f;

		switch(this->moveDir)
		{
		case Move_X:
			
			(*poTrans)[x] += (delta * dirX);
			if(this->poTrans->x() > 6.0f || this->poTrans->x() < -6.0f)
			{
				dirX *= -1.0f;
			}
			break;

		case Move_Y:
			(*poTrans)[y] += (delta * dirY);
			if(this->poTrans->y() > 4.0f || this->poTrans->y() < -4.0f)
			{
				dirY *= -1.0f;
			}
			break;

		case Move_Z:
			(*poTrans)[z] += (delta * dirZ);
			if(this->poTrans->z() > 7.0f || this->poTrans->z() < -5.0f)
			{
				dirZ *= -1.0f;
			}
			break;

		case Move_None:
		default:
			break;
		}

		// Goal: update the world matrix

		this->rotY += deltaRotY;
		this->rotZ += deltaRotZ;

		Mat4 Scale(Mat4::Scale::XYZ, *this->poScale);
		Mat4 TransA(Mat4::Trans::XYZ, *this->poTrans);
		Mat4 RotY(Mat4::Rot1::Y, this->rotY);
		Mat4 RotZ(Mat4::Rot1::Z, this->rotZ);

		// world matrix
		*this->poWorld = Scale * RotY * RotZ * TransA;
	}

	void SimpleGameObject::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void SimpleGameObject::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void SimpleGameObject::SetPos(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

}

// --- End of File ---
