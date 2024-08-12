//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "GraphicsObject.h"
#include "PCSNode.h"

namespace Azul
{

	class GameObject : public PCSNode
	{
	public:
		GameObject() = delete;
		GameObject(const GameObject &) = delete;
		GameObject &operator = (const GameObject &) = delete;
		virtual ~GameObject();

		GameObject(GraphicsObject *graphicsObject);  // Keenan(20)

		void Update(float t);
		void Draw();

		// Set / Get:
		GraphicsObject *GetGraphicsObject();
		Mat4 *GetWorld();

		void SetWorld(Mat4 *pWorld);
		void SetPos(const Vec3 &pos);
		void SetScale(const Vec3 &scale);
		void SetDeltaRot(float delta);

	protected:
		Mat4 *poWorld;
		Vec3 *poTrans;

	private:
		void privUpdate(float t);

		GraphicsObject *poGraphicsObject;
		Vec3 *poScale;

		float           deltaRot;
		float			rotY;
		float			rotZ;
	};
}

#endif


// --- End of File ---
