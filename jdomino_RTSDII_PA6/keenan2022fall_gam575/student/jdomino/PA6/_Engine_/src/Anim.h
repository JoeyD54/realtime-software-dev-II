//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "Clip.h"
#include "Skeleton.h"

namespace Azul
{
	#define NUM_BONES 12

	class Anim
	{
	public:
		Anim(Skeleton::Position pos, Clip* clip);
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		~Anim();

		void Animate(AnimTime tCurr);
		AnimTime FindMaxTime();

		void SetLocation(Skeleton::Position pos);
		static void PoseSkeleton(GameObjectAnimSkeleton *node);

	private:
		int              numBones;
		Clip            *pClip;
		Bone            *poBoneResult;
		Skeleton        *poSkeleton;	
	};

}
#endif

// --- End of File ---