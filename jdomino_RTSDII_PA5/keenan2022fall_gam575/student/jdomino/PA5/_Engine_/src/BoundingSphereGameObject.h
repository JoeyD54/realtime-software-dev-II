//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOUNDING_SPHERE_GAME_OBJECT_H
#define BOUNDING_SPHERE_GAME_OBJECT_H

#include "MathEngine.h"
#include "GameObject.h"
#include "AnimTime.h"

namespace Azul
{
	class BoundingSphereGameObject : public GameObject
	{
	public:
		BoundingSphereGameObject(GraphicsObject *graphicsObject);

		// Big four
		BoundingSphereGameObject() = delete;
		BoundingSphereGameObject(const BoundingSphereGameObject &) = delete;
		BoundingSphereGameObject &operator=(BoundingSphereGameObject &) = delete;
		virtual ~BoundingSphereGameObject();

		void SetBoundingSphereReference(GameObject *pGameObj);

		virtual void Update(AnimTime currTime) override;

	private:
		void privUpdate(AnimTime currTime);
		void privUpdateBoundingSphereReference(AnimTime currentTime);

		// Data: ------------------
		GameObject *pRefGameObj;

	public:
		Vec3 *poScale;
		Vec3 *poTrans;
	};

}

#endif

// --- End of File ---
