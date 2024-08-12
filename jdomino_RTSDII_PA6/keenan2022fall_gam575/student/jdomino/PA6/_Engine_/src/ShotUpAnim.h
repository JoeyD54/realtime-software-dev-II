#ifndef SHOT_UP_ANIM_H
#define SHOT_UP_ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "ShotUpClip.h"
#include "Skeleton.h"

namespace Azul
{
#define NUM_BONES 12

	class ShotUpAnim
	{
	public:
		ShotUpAnim();
		ShotUpAnim(const ShotUpAnim&) = delete;
		ShotUpAnim& operator = (const ShotUpAnim&) = delete;
		~ShotUpAnim();

		void Animate(AnimTime tCurr);
		AnimTime FindMaxTime();

		static void PoseSkeleton(GameObjectAnimSkeleton* node);

		void SetLocation(Skeleton::Position newPos);

	private:
		ShotUpClip* pClip;
		Bone* poBoneResult;
		Skeleton* poSkeleton;
		int         numBones;
	};
}
#endif

// --- End of File ---