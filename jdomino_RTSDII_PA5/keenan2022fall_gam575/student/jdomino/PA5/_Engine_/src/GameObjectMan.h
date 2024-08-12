//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "AnimTime.h"

namespace Azul
{

	// Singleton
	class GameObjectMan
	{
	public:
		static void Add(GameObject *pObj);
		static void Draw(void);
		static void Update(AnimTime currentTime);

		static void Create();
		static void Destroy();
		~GameObjectMan();

	private:
		GameObjectMan();

		static GameObjectMan *privGetInstance();

		// data
		PCSTree *poRootTree;
	};

}

#endif


// --- End of File ---
