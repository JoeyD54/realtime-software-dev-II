//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CLIP_H
#define CLIP_H

#include "AnimTime.h"
#include "Bone.h"

namespace Azul
{
	class Clip
	{
	public:

		enum ClipType
		{
			WALK,
			SIDESTEP,
			TURNRIGHT,
			RUN,
			DIELEFT,
			SHOTUP
		};

		struct FrameBucket
		{
			~FrameBucket()
			{
				delete[] poBone;
			}

			FrameBucket *nextBucket;
			FrameBucket *prevBucket;
			AnimTime      KeyTime;
			Bone         *poBone;
			char          pad[4];
		};

	public:
		Clip(int _numFrames, ClipType clipType);

		Clip() = delete;
		Clip(const Clip &) = delete;
		Clip &operator = (const Clip &) = delete;
		~Clip();

		AnimTime GetTotalTime();
		void AnimateBones(AnimTime tCurr, Bone *pResult);

	private:
		void privSetWalkAnimationData();
		void privSetRunAnimationData();
		void privSetSideStepAnimationData();
		void privSetShotUpAnimationData();
		void privSetTurnRightAnimationData();
		void privSetDieLeftAnimationData();

		AnimTime privFindMaxTime();
		int  privFindNumFrames();

	private:
		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket *poHead;
	};
}

#endif

//--- End of File ---
