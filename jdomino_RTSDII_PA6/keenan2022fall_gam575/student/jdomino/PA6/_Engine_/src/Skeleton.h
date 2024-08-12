//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include "GameObjectAnim.h"
#include "Bone.h"
#include "GameObjectBasic.h"

namespace Azul
{
	class Skeleton
	{
	public:
		struct Data
		{
			int  index;
			int  parentIndex;
			char name[64];
		};

		enum Position
		{
			CENTER,
			TOPRIGHT,
			TOPLEFT,
			BOTTOMRIGHT,
			BOTTOMLEFT
		};

	public:
		Skeleton(Bone *pBone, int numBones);
		Skeleton(Bone* pBone, int numBones, Skeleton::Position pos);

		Skeleton() = delete;
		Skeleton(const Skeleton &) = delete;
		Skeleton &operator = (const Skeleton &) = delete;
		~Skeleton();

		void SetLocation(Skeleton::Position pos);
		GameObjectAnim *GetFirstBone();

	private:
		void privSetAnimationHierarchy(Bone *pBoneResult);
		GameObjectAnim *privFindBoneByIndex(int index);

	private:
		GameObjectAnim *pFirstBone;
		int             numBones;
		Position		myPos;
		GameObjectBasic* pPivot;
	};
}

#endif

// --- End of File ---
