//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SIMPLE_GAME_OBJECT_H
#define SIMPLE_GAME_OBJECT_H

#include "GameObject.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"

namespace Azul
{
	class SimpleGameObject : public GameObject
	{
	public:
		enum MoveDir
		{
			Move_X,
			Move_Y,
			Move_Z,
			Move_None
		};
	
	public:
		SimpleGameObject(GraphicsObject *graphicsObject);

		// Big four
		SimpleGameObject() = delete;
		SimpleGameObject(const SimpleGameObject &) = delete;
		SimpleGameObject &operator=(SimpleGameObject &) = delete;
		virtual ~SimpleGameObject();

		virtual void Update(AnimTime currTime);

		void SetScale(float sx, float sy, float sz);
		void SetPos(float x, float y, float z);

		void setMove(MoveDir move);

	private:
		void privUpdate(AnimTime currTime);

	public:   // add accessors later
		Vec3 *poScale;
		Vec3 *poTrans;

		float deltaRotY;
		float deltaRotZ;
		float rotY;
		float rotZ;

		MoveDir moveDir;

	};

}

#endif

// --- End of File ---
