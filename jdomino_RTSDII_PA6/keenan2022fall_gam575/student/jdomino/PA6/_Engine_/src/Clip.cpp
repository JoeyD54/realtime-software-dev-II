//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"

namespace Azul
{
	Clip::Clip( int _numBones, ClipType clipType )
	: numBones(_numBones),
	numFrames(0),
	TotalTime(AnimTime::Duration::ZERO),
	poHead(nullptr)
	{
		if (clipType == ClipType::WALK)
		{
			this->privSetWalkAnimationData();
		}
		else if (clipType == ClipType::RUN)
		{
			this->privSetRunAnimationData();
		}
		else if (clipType == ClipType::SIDESTEP)
		{
			this->privSetSideStepAnimationData();
		}
		else if (clipType == ClipType::SHOTUP)
		{
			this->privSetShotUpAnimationData();
		}
		else if (clipType == ClipType::TURNRIGHT)
		{
			this->privSetTurnRightAnimationData();
		}
		else if (clipType == ClipType::DIELEFT)
		{
			this->privSetDieLeftAnimationData();
		}
		
		this->TotalTime = this->privFindMaxTime();
		this->numFrames = this->privFindNumFrames();
	}

	Clip::~Clip()
	{
		FrameBucket *pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket *pDeleteMe = pTmp;		
			pTmp = pTmp->nextBucket;			
			delete pDeleteMe;
		}		
	}

	void Clip::AnimateBones(AnimTime tCurr, Bone *pResult)
	{
		// First one 
		FrameBucket *pTmp = this->poHead;

		// Find which key frames
		while(tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket *pA = pTmp->prevBucket;
		FrameBucket *pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->numBones);

	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

	float scale = 1.0f;

	void Clip::privSetWalkAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket *pTmp = nullptr;
		FrameBucket *pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000500f, -0.020833f, 0.007737f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273342f, 0.650441f, 0.641298f, 0.301576f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480434f, -0.518829f, 0.518829f, 0.480434f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.926996f, 0.010783f, -0.374829f, -0.008046f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142469f, 0.693114f, -0.668960f, 0.227570f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571355f, -0.416597f, -0.416598f, 0.571355f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939128f, -0.065612f, -0.336303f, 0.025158f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026878f, 0.001573f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000500f, -0.015882f, 0.011317f, 0.999810f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.248711f, 0.660774f, 0.651723f, 0.277088f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.492427f, -0.507460f, 0.507460f, 0.492427f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.919628f, 0.007867f, -0.392664f, -0.006086f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.157052f, 0.689055f, -0.665764f, 0.239365f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.581072f, -0.402934f, -0.402935f, 0.581071f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.951171f, -0.067765f, -0.300205f, 0.023637f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027222f, 0.001670f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000499f, -0.009405f, 0.014569f, 0.999849f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.219280f, 0.671673f, 0.662507f, 0.248707f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.508527f, -0.491325f, 0.491326f, 0.508526f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.912469f, 0.005930f, -0.409080f, -0.004349f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.172767f, 0.684337f, -0.662070f, 0.251989f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.589800f, -0.390046f, -0.390046f, 0.589800f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.961425f, -0.069354f, -0.265285f, 0.021808f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027433f, 0.001728f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000497f, -0.002066f, 0.017413f, 0.999846f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.186397f, 0.682144f, 0.672744f, 0.217604f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.528093f, -0.470231f, 0.470232f, 0.528093f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.906576f, 0.004900f, -0.422005f, -0.002822f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.189777f, 0.678816f, -0.657657f, 0.265858f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.596910f, -0.379076f, -0.379077f, 0.596909f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.969887f, -0.070408f, -0.232303f, 0.019922f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027504f, 0.001748f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000495f, 0.005272f, 0.019790f, 0.999790f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.150795f, 0.691574f, 0.681919f, 0.184316f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.550164f, -0.444207f, 0.444207f, 0.550164f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.902516f, 0.004665f, -0.430629f, -0.001479f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.207858f, 0.672464f, -0.652450f, 0.280884f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.602208f, -0.370601f, -0.370602f, 0.602208f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.976750f, -0.070934f, -0.201488f, 0.018145f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027417f, 0.001726f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000491f, 0.011749f, 0.021659f, 0.999696f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.113161f, 0.699465f, 0.689648f, 0.149429f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.573042f, -0.414273f, 0.414274f, 0.573042f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.900070f, 0.005147f, -0.435715f, -0.000345f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.226970f, 0.665203f, -0.646327f, 0.297071f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.605371f, -0.365412f, -0.365413f, 0.605370f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.982189f, -0.070909f, -0.173207f, 0.016630f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027156f, 0.001662f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000486f, 0.016699f, 0.022997f, 0.999596f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.074389f, 0.705436f, 0.695611f, 0.113806f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.594617f, -0.382663f, 0.382663f, 0.594617f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.898272f, 0.006319f, -0.439393f, 0.000531f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.247223f, 0.656894f, -0.639114f, 0.314492f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.606099f, -0.364203f, -0.364203f, 0.606099f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.986410f, -0.070289f, -0.147697f, 0.015472f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026738f, 0.001554f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000480f, 0.019743f, 0.023797f, 0.999522f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.035425f, 0.709271f, 0.699671f, 0.078363f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.613264f, -0.352004f, 0.352005f, 0.613264f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.895964f, 0.008159f, -0.444051f, 0.001071f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.268153f, 0.647592f, -0.630968f, 0.332563f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.604882f, -0.366221f, -0.366222f, 0.604881f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.989761f, -0.068983f, -0.124093f, 0.014656f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026205f, 0.001404f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000472f, 0.020754f, 0.024061f, 0.999495f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.002603f, 0.711036f, 0.701761f, 0.044183f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.627851f, -0.325274f, 0.325274f, 0.627851f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.891876f, 0.010697f, -0.452152f, 0.001286f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.288816f, 0.637658f, -0.622406f, 0.350126f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.602842f, -0.369570f, -0.369571f, 0.602841f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.992561f, -0.066852f, -0.100782f, 0.014040f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025631f, 0.001213f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000460f, 0.019504f, 0.023768f, 0.999527f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.038679f, 0.711091f, 0.701930f, 0.012171f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.637796f, -0.305313f, 0.305314f, 0.637796f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.884793f, 0.013967f, -0.465774f, 0.001253f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.307599f, 0.628259f, -0.614188f, 0.365304f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.601669f, -0.371476f, -0.371477f, 0.601668f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.994988f, -0.063914f, -0.075778f, 0.013073f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025098f, 0.000986f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000444f, 0.015755f, 0.022881f, 0.999614f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.008006f, 0.712285f, 0.700156f, 0.048655f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.612932f, -0.352582f, 0.352583f, 0.612932f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.873157f, 0.018841f, -0.487073f, -0.001489f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.316669f, 0.624309f, -0.609920f, 0.371424f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.580290f, -0.404060f, -0.404060f, 0.580289f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.991437f, -0.060584f, -0.114703f, 0.015010f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024680f, 0.000728f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000418f, 0.009732f, 0.021398f, 0.999724f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.016885f, 0.712305f, 0.697119f, 0.079754f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.591023f, -0.388190f, 0.388191f, 0.591023f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.866422f, 0.024358f, -0.498694f, -0.004885f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.324051f, 0.621116f, -0.606707f, 0.375649f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.558394f, -0.433816f, -0.433817f, 0.558393f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.986751f, -0.056417f, -0.151207f, 0.016617f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024419f, 0.000447f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000355f, 0.002069f, 0.019329f, 0.999811f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.037331f, 0.711548f, 0.693499f, 0.106607f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.573264f, -0.413967f, 0.413968f, 0.573263f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.864757f, 0.030316f, -0.501195f, -0.008890f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.329252f, 0.619012f, -0.604930f, 0.377461f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.536924f, -0.460123f, -0.460123f, 0.536923f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.981152f, -0.051441f, -0.185416f, 0.017754f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024332f, 0.000151f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000281f, -0.006200f, 0.016707f, 0.999841f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.054648f, 0.710167f, 0.689732f, 0.130181f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.560306f, -0.431344f, 0.431344f, 0.560305f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.867909f, 0.036419f, -0.495207f, -0.013330f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.332036f, 0.618233f, -0.604710f, 0.376650f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.516745f, -0.482675f, -0.482675f, 0.516744f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.974759f, -0.045821f, -0.217748f, 0.018197f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024403f, -0.000151f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000203f, -0.013863f, 0.013581f, 0.999812f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.070259f, 0.708319f, 0.685897f, 0.151307f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.552078f, -0.441825f, 0.441826f, 0.552078f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.875028f, 0.042433f, -0.481886f, -0.017656f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.332281f, 0.618857f, -0.606078f, 0.373196f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.498627f, 0.501369f, 0.501370f, -0.498627f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.967584f, -0.039758f, -0.248757f, 0.017878f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024614f, -0.000447f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000127f, -0.019885f, 0.010029f, 0.999752f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.085088f, 0.705989f, 0.682119f, 0.170453f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.548460f, -0.446309f, 0.446310f, 0.548459f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.885259f, 0.048120f, -0.462104f, -0.021448f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.329397f, 0.621178f, -0.609281f, 0.366621f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.483850f, 0.515645f, 0.515645f, -0.483849f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.959699f, -0.033480f, -0.278525f, 0.016779f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024958f, -0.000728f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000058f, -0.023634f, 0.006154f, 0.999702f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.099498f, 0.703230f, 0.678514f, 0.187580f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.549407f, -0.445143f, 0.445143f, 0.549406f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.897839f, 0.053287f, -0.436415f, -0.024264f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.322454f, 0.625596f, -0.614657f, 0.356160f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.474019f, 0.524696f, 0.524696f, -0.474019f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.951332f, -0.027243f, -0.306594f, 0.014980f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025408f, -0.000986f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.024883f, 0.002074f, 0.999688f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.113640f, 0.700198f, 0.675095f, 0.202621f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.554394f, -0.438916f, 0.438917f, 0.554394f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.911767f, 0.057834f, -0.405799f, -0.025744f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.310883f, 0.632168f, -0.622143f, 0.341545f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.470141f, 0.528174f, 0.528174f, -0.470141f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.942819f, -0.021356f, -0.332378f, 0.012707f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025918f, -0.001213f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000057f, -0.023872f, -0.002074f, 0.999713f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.127511f, 0.696929f, 0.671922f, 0.215756f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.562362f, -0.428660f, 0.428660f, 0.562361f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.925947f, 0.061685f, -0.371677f, -0.025963f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.294626f, 0.640563f, -0.631274f, 0.323060f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.472319f, 0.526227f, 0.526228f, -0.472318f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.934539f, -0.016118f, -0.355346f, 0.010279f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, -0.001404f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000120f, -0.020829f, -0.006154f, 0.999764f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.141437f, 0.693348f, 0.668891f, 0.227704f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.571884f, -0.415871f, 0.415871f, 0.571884f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.939377f, 0.064817f, -0.335760f, -0.025199f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.274283f, 0.650094f, -0.641253f, 0.301565f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.479835f, 0.519382f, 0.519383f, -0.479835f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.926825f, -0.011770f, -0.375226f, 0.007977f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026878f, -0.001554f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000189f, -0.015880f, -0.010030f, 0.999824f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.156065f, 0.689287f, 0.665692f, 0.239543f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.581520f, -0.402286f, 0.402287f, 0.581520f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.951353f, 0.067269f, -0.299730f, -0.023760f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.251491f, 0.659718f, -0.651004f, 0.278780f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.491527f, 0.508331f, 0.508332f, -0.491527f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.920266f, -0.008445f, -0.391156f, 0.005974f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027222f, -0.001662f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000259f, -0.009404f, -0.013582f, 0.999864f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.171902f, 0.684548f, 0.662007f, 0.252171f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.590159f, -0.389503f, 0.389504f, 0.590159f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.961549f, 0.069082f, -0.264894f, -0.021963f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.227762f, 0.668701f, -0.659814f, 0.256141f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.505745f, -0.494188f, -0.494188f, 0.505745f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.915030f, -0.006172f, -0.403316f, 0.004348f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027433f, -0.001726f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000327f, -0.002066f, -0.016707f, 0.999858f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.189091f, 0.678990f, 0.657611f, 0.266014f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.597174f, -0.378659f, 0.378660f, 0.597174f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.969963f, 0.070281f, -0.232010f, -0.020068f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.203366f, 0.676942f, -0.667652f, 0.233737f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.521135f, -0.477932f, -0.477932f, 0.521134f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.910683f, -0.004911f, -0.413065f, 0.003082f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027504f, -0.001748f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000388f, 0.005272f, -0.019329f, 0.999799f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.207390f, 0.672588f, 0.652426f, 0.280991f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.602382f, -0.370319f, 0.370320f, 0.602381f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.976793f, 0.070872f, -0.201296f, -0.018253f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.177994f, 0.684522f, -0.674691f, 0.211042f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.536922f, -0.460125f, -0.460125f, 0.536921f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.906845f, -0.004587f, -0.421434f, 0.002110f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027433f, -0.001728f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000445f, 0.011748f, -0.021398f, 0.999702f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.226342f, 0.665415f, 0.646472f, 0.296761f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.605849f, -0.364619f, 0.364620f, 0.605849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.982293f, 0.070882f, -0.172623f, -0.016628f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.151053f, 0.691525f, -0.681124f, 0.187206f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.552709f, -0.441036f, -0.441036f, 0.552709f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.903195f, -0.005069f, -0.429199f, 0.001355f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027222f, -0.001670f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000472f, 0.016699f, -0.022881f, 0.999599f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.245641f, 0.657533f, 0.639774f, 0.313050f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.607636f, -0.361633f, 0.361634f, 0.607636f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.986691f, 0.070311f, -0.145821f, -0.015288f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.121894f, 0.697923f, -0.687019f, 0.161403f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.568206f, -0.420882f, -0.420883f, 0.568205f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.899371f, -0.006268f, -0.437141f, 0.000751f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026878f, -0.001573f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000471f, 0.019743f, -0.023768f, 0.999522f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.264971f, 0.648994f, 0.632498f, 0.329458f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.608038f, -0.360957f, 0.360958f, 0.608038f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.990221f, 0.069072f, -0.120364f, -0.014284f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.089679f, 0.703541f, -0.692362f, 0.132747f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.583457f, -0.399472f, -0.399473f, 0.583456f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.895123f, -0.008119f, -0.445746f, 0.000349f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, -0.001437f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000467f, 0.020754f, -0.024061f, 0.999495f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.283769f, 0.640053f, 0.624981f, 0.345263f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.607754f, -0.361434f, 0.361434f, 0.607754f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.993101f, 0.067074f, -0.095232f, -0.013508f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.053302f, 0.708164f, -0.696895f, 0.099999f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.598964f, -0.375822f, -0.375823f, 0.598963f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.890456f, -0.010573f, -0.454947f, 0.000050f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 28  time: 1.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 28 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025918f, -0.001264f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000458f, 0.019743f, -0.023797f, 0.999522f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.301135f, 0.631494f, 0.617595f, 0.359317f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.607884f, -0.361216f, 0.361216f, 0.607884f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.995453f, 0.064386f, -0.069072f, -0.012490f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.011102f, 0.711132f, -0.700272f, 0.061532f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.615511f, -0.348060f, -0.348061f, 0.615511f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.885597f, -0.013539f, -0.464258f, -0.000041f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 29  time: 1.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 29 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025408f, -0.001058f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000442f, 0.016699f, -0.022997f, 0.999596f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.315822f, 0.624065f, 0.611350f, 0.370204f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.609744f, -0.358067f, 0.358068f, 0.609744f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.997263f, 0.060875f, -0.040447f, -0.011197f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.038623f, 0.711525f, -0.701429f, 0.015452f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.633004f, -0.315129f, -0.315130f, 0.633003f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.879920f, -0.016969f, -0.474820f, -0.000164f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 30  time: 1.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 30 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024958f, -0.000822f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000418f, 0.011748f, -0.021658f, 0.999696f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.323346f, 0.620904f, 0.607842f, 0.374771f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588243f, -0.392390f, 0.392390f, 0.588243f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.994832f, 0.057129f, -0.082888f, -0.013207f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.010273f, 0.712678f, -0.699672f, 0.049439f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.609650f, -0.358228f, -0.358229f, 0.609649f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.870023f, -0.022054f, -0.492509f, 0.002900f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 31  time: 1.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 31 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024614f, -0.000562f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000385f, 0.005272f, -0.019789f, 0.999790f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.329223f, 0.618520f, 0.605339f, 0.377637f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.565991f, -0.423856f, 0.423856f, 0.565991f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.990819f, 0.052733f, -0.123599f, -0.014850f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.013425f, 0.712754f, -0.696818f, 0.079038f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.589173f, -0.390993f, -0.390993f, 0.589172f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.864715f, -0.027624f, -0.501460f, 0.006530f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 32  time: 1.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 32 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024403f, -0.000285f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000323f, -0.002067f, -0.017413f, 0.999846f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.333280f, 0.617035f, 0.603998f, 0.378653f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543638f, -0.452170f, 0.452171f, 0.543638f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.985377f, 0.047746f, -0.162775f, -0.016046f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.033764f, 0.712044f, -0.693369f, 0.105319f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.572382f, -0.415186f, -0.415187f, 0.572381f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.863928f, -0.033488f, -0.502388f, 0.010621f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 33  time: 1.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 33 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024332f, 0.000000f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000254f, -0.009404f, -0.014568f, 0.999850f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.335359f, 0.616596f, 0.603902f, 0.377686f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.522016f, -0.476969f, 0.476970f, 0.522015f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.978640f, 0.042307f, -0.200493f, -0.016634f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.051849f, 0.710613f, -0.689692f, 0.129097f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.559737f, -0.432081f, -0.432082f, 0.559737f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.867350f, -0.039380f, -0.495911f, 0.015036f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 34  time: 1.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 34 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024403f, 0.000285f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000184f, -0.015881f, -0.011316f, 0.999810f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.335035f, 0.617471f, 0.605281f, 0.374320f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.502364f, -0.497624f, 0.497625f, 0.502364f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.970790f, 0.036575f, -0.236552f, -0.016508f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.068620f, 0.708621f, -0.685870f, 0.150765f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.551482f, -0.442569f, -0.442570f, 0.551482f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.874467f, -0.045089f, -0.482603f, 0.019227f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 35  time: 1.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 35 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024614f, 0.000562f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000116f, -0.020830f, -0.007736f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.331470f, 0.620114f, 0.608568f, 0.367739f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.486415f, -0.513226f, 0.513226f, 0.486414f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.962135f, 0.030724f, -0.270387f, -0.015622f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.084540f, 0.706109f, -0.682085f, 0.170361f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.547848f, -0.447060f, -0.447061f, 0.547847f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.884722f, -0.050396f, -0.462827f, 0.022783f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 36  time: 1.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 36 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024958f, 0.000822f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000054f, -0.023874f, -0.003927f, 0.999707f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.323806f, 0.624881f, 0.614068f, 0.357204f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.475791f, -0.523090f, 0.523091f, 0.475790f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.953085f, 0.024978f, -0.301342f, -0.014058f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.099762f, 0.703188f, -0.678484f, 0.187705f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.548791f, -0.445901f, -0.445902f, 0.548791f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.897346f, -0.055141f, -0.437138f, 0.025313f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 37  time: 1.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 37 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025408f, 0.001058f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.024885f, -0.000000f, 0.999690f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.311538f, 0.631790f, 0.621697f, 0.342460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.471420f, -0.527032f, 0.527032f, 0.471420f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.944075f, 0.019603f, -0.328929f, -0.012030f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.114334f, 0.700057f, -0.675104f, 0.202691f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.553789f, -0.439679f, -0.439679f, 0.553789f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.911336f, -0.059260f, -0.406512f, 0.026513f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 38  time: 1.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 38 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025918f, 0.001264f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000054f, -0.023873f, 0.003927f, 0.999707f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.294653f, 0.640481f, 0.630971f, 0.323789f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.473259f, -0.525382f, 0.525382f, 0.473259f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.935406f, 0.014862f, -0.353126f, -0.009829f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.128386f, 0.696741f, -0.671979f, 0.215671f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.561788f, -0.429412f, -0.429413f, 0.561787f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.925587f, -0.062709f, -0.372363f, 0.026487f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 39  time: 1.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 39 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000116f, -0.020830f, 0.007736f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273412f, 0.650407f, 0.641251f, 0.301684f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480448f, -0.518816f, 0.518817f, 0.480447f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.927060f, 0.010960f, -0.374673f, -0.007709f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142395f, 0.693133f, -0.668972f, 0.227524f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571363f, -0.416587f, -0.416588f, 0.571362f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939094f, -0.065492f, -0.336395f, 0.025523f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
	}


	void Clip::privSetRunAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000500f, -0.020833f, 0.007737f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273342f, 0.650441f, 0.641298f, 0.301576f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480434f, -0.518829f, 0.518829f, 0.480434f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.926996f, 0.010783f, -0.374829f, -0.008046f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142469f, 0.693114f, -0.668960f, 0.227570f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571355f, -0.416597f, -0.416598f, 0.571355f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939128f, -0.065612f, -0.336303f, 0.025158f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.029278f, 0.000000f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, -0.004239f, 0.013590f, 0.999899f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.071097f, 0.712060f, 0.698260f, 0.018682f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.655043f, -0.266307f, 0.266307f, 0.655042f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.912355f, 0.050050f, -0.406216f, -0.009562f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.322482f, 0.619251f, -0.605391f, 0.382145f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.609518f, -0.358452f, -0.358452f, 0.609518f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.998394f, -0.054851f, -0.005081f, 0.013241f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.028823f, -0.000687f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000003f, 0.003998f, 0.009633f, 0.999946f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.007374f, 0.713090f, 0.694619f, 0.094620f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.645959f, -0.287641f, 0.287641f, 0.645958f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.933659f, 0.062262f, -0.352442f, -0.013761f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.359474f, 0.599715f, -0.585854f, 0.409752f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.553955f, -0.439471f, -0.439471f, 0.553954f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.994042f, -0.043581f, -0.098740f, 0.015198f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027542f, -0.001341f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000012f, 0.009405f, 0.005010f, 0.999943f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.075003f, 0.705698f, 0.678006f, 0.191502f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.610632f, -0.356551f, 0.356552f, 0.610631f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.937199f, 0.076533f, -0.339569f, -0.022198f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.386524f, 0.584164f, -0.570514f, 0.428795f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.475809f, 0.523073f, 0.523074f, -0.475809f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.973654f, -0.032284f, -0.225133f, 0.016452f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025896f, -0.001876f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000028f, 0.011232f, -0.000000f, 0.999937f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.150338f, 0.688559f, 0.650997f, 0.281935f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.567252f, -0.422168f, 0.422168f, 0.567251f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.938701f, 0.090894f, -0.330871f, -0.033204f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.391189f, 0.583319f, -0.569798f, 0.426661f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.398316f, 0.584247f, 0.584247f, -0.398316f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933164f, -0.022189f, -0.358447f, 0.015117f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024614f, -0.002240f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000052f, 0.007652f, -0.005533f, 0.999955f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.210475f, 0.665541f, 0.624120f, 0.351040f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543793f, -0.451983f, 0.451983f, 0.543793f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.952414f, 0.100768f, -0.284621f, -0.041765f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.366897f, 0.600940f, -0.588143f, 0.397926f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.348862f, 0.615058f, 0.615058f, -0.348861f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.881744f, -0.013885f, -0.471372f, 0.011952f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024159f, -0.002377f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000197f, -0.002436f, -0.011232f, 0.999934f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.250448f, 0.646723f, 0.607617f, 0.387074f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.551074f, -0.443078f, 0.443078f, 0.551073f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.973107f, 0.103494f, -0.201607f, -0.041314f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.304640f, 0.636548f, -0.622721f, 0.337963f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.337490f, 0.621370f, 0.621370f, -0.337489f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.825828f, -0.010427f, -0.563740f, 0.009897f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024475f, -0.002305f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000384f, -0.015389f, -0.016066f, 0.999752f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.267589f, 0.638620f, 0.607018f, 0.389986f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.585908f, -0.395869f, 0.395869f, 0.585907f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.990215f, 0.099691f, -0.092053f, -0.032578f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.207744f, 0.676963f, -0.660480f, 0.249659f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.364214f, 0.606093f, 0.606093f, -0.364213f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.774464f, -0.012423f, -0.632422f, 0.009732f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025396f, -0.002092f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000530f, -0.025475f, -0.019064f, 0.999494f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.256258f, 0.644416f, 0.623592f, 0.360823f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.641701f, -0.297019f, 0.297019f, 0.641700f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.994580f, 0.091792f, 0.045122f, -0.018656f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.107080f, 0.703133f, -0.684881f, 0.158356f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.424052f, 0.565844f, 0.565845f, -0.424051f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.756151f, -0.017072f, -0.654103f, 0.009645f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026719f, -0.001741f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000529f, -0.029054f, -0.020001f, 0.999378f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.236419f, 0.653785f, 0.640217f, 0.326793f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.670798f, -0.223673f, 0.223673f, 0.670798f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.989536f, 0.083128f, 0.117448f, -0.010663f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.024724f, 0.713651f, -0.694879f, 0.085053f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.498206f, 0.501788f, 0.501788f, -0.498205f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.776075f, -0.023361f, -0.630137f, 0.009412f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.028042f, -0.001263f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000518f, -0.026567f, -0.019267f, 0.999461f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.255984f, 0.647882f, 0.633611f, 0.336540f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.656303f, -0.263187f, 0.263187f, 0.656302f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.993998f, 0.075462f, 0.078319f, -0.011823f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.033420f, 0.715274f, -0.697085f, 0.036585f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.565043f, -0.425120f, -0.425120f, 0.565042f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.815762f, -0.031033f, -0.577475f, 0.009610f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.028962f, -0.000673f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000493f, -0.019326f, -0.016966f, 0.999669f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.286692f, 0.635817f, 0.621093f, 0.357476f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.635033f, -0.311020f, 0.311021f, 0.635032f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.997013f, 0.066200f, 0.037673f, -0.012818f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.067189f, 0.713894f, -0.696898f, 0.013204f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.613249f, -0.352031f, -0.352032f, 0.613248f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.857049f, -0.040303f, -0.513551f, 0.010370f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.029278f, 0.000000f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000384f, -0.008912f, -0.013224f, 0.999873f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.321820f, 0.619530f, 0.605276f, 0.382434f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.606762f, -0.363097f, 0.363098f, 0.606762f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.998357f, 0.055045f, -0.008311f, -0.013579f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.074264f, 0.712839f, -0.697184f, 0.016752f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.642484f, -0.295322f, -0.295323f, 0.642483f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.893687f, -0.051011f, -0.445628f, 0.011728f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.028823f, 0.000718f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000251f, 0.001501f, -0.008646f, 0.999961f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.359917f, 0.599308f, 0.585061f, 0.411087f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.549811f, -0.444643f, 0.444644f, 0.549811f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.993515f, 0.043109f, -0.104066f, -0.015506f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.044636f, 0.714035f, -0.696270f, 0.058054f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.644942f, -0.289914f, -0.289915f, 0.644941f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.913431f, -0.063406f, -0.401746f, 0.014976f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027542f, 0.001386f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000118f, 0.008744f, -0.004044f, 0.999954f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.386674f, 0.584074f, 0.570204f, 0.429195f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.471740f, -0.526746f, 0.526746f, 0.471740f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.972170f, 0.031467f, -0.231575f, -0.016403f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.020007f, 0.713239f, -0.687252f, 0.136289f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.617903f, -0.343797f, -0.343798f, 0.617902f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.916016f, -0.077228f, -0.393035f, 0.021764f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025896f, 0.001918f, 0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, 0.011232f, 0.000000f, 0.999937f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.390855f, 0.583794f, 0.570676f, 0.425142f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.396063f, -0.585777f, 0.585777f, 0.396062f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.931210f, 0.021429f, -0.363559f, -0.014649f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.095889f, 0.703003f, -0.666745f, 0.228131f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.573392f, -0.413790f, -0.413791f, 0.573391f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.915140f, -0.091205f, -0.391302f, 0.032909f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024614f, 0.002259f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000128f, 0.007652f, 0.004407f, 0.999961f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.368076f, 0.600436f, 0.588414f, 0.397197f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.348400f, -0.615319f, 0.615319f, 0.348399f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.881566f, 0.013687f, -0.471719f, -0.011660f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.162047f, 0.684330f, -0.641669f, 0.306095f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.537867f, -0.459020f, -0.459020f, 0.537866f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.924908f, -0.101523f, -0.363747f, 0.043885f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024159f, 0.002377f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000288f, -0.002436f, 0.009901f, 0.999948f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.312444f, 0.632618f, 0.619347f, 0.344358f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.336995f, -0.621638f, 0.621638f, 0.336995f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.831697f, 0.010586f, -0.555037f, -0.010137f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.211811f, 0.665110f, -0.622652f, 0.353651f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.532418f, -0.465329f, -0.465330f, 0.532417f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.948500f, -0.104644f, -0.295388f, 0.046306f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024391f, 0.002316f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000442f, -0.015390f, 0.015218f, 0.999766f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.228328f, 0.669670f, 0.653365f, 0.269300f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.357414f, -0.610127f, 0.610127f, 0.357413f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.786357f, 0.012196f, -0.617566f, -0.010310f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.243815f, 0.651402f, -0.614463f, 0.372377f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.554195f, -0.439168f, -0.439168f, 0.554194f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.973904f, -0.101785f, -0.198840f, 0.040160f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025078f, 0.002145f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000547f, -0.025475f, 0.018816f, 0.999498f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.139272f, 0.696431f, 0.677950f, 0.189659f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.403353f, -0.580781f, 0.580781f, 0.403353f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.762551f, 0.016096f, -0.646643f, -0.010475f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.255935f, 0.646259f, -0.617799f, 0.367656f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.596591f, -0.379578f, -0.379578f, 0.596590f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.991632f, -0.095469f, -0.081964f, 0.028874f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026125f, 0.001880f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000545f, -0.029054f, 0.020001f, 0.999378f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.062194f, 0.710158f, 0.690926f, 0.120118f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.464498f, -0.533143f, 0.533144f, 0.464497f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.767507f, 0.021176f, -0.640610f, -0.010176f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.240632f, 0.652469f, -0.635242f, 0.335927f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.654887f, -0.266689f, -0.266690f, 0.654887f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.994122f, -0.086472f, 0.063429f, 0.014844f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027312f, 0.001530f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000525f, -0.027227f, 0.019695f, 0.999435f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.002304f, 0.714893f, 0.695983f, 0.067315f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.526465f, -0.472054f, 0.472054f, 0.526464f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.793176f, 0.026956f, -0.608314f, -0.009908f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.221153f, 0.660236f, -0.649814f, 0.304830f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.682594f, -0.184571f, -0.184571f, 0.682593f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.986402f, -0.078243f, 0.144356f, 0.007104f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.028359f, 0.001102f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000477f, -0.021822f, 0.018637f, 0.999588f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.040022f, 0.715169f, 0.697026f, 0.032948f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.577871f, -0.407511f, 0.407512f, 0.577870f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.826411f, 0.033688f, -0.561971f, -0.009912f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.252512f, 0.649768f, -0.637068f, 0.328913f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.662572f, -0.246979f, -0.246980f, 0.662571f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.993343f, -0.072042f, 0.089347f, 0.009893f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.029046f, 0.000595f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000358f, -0.013585f, 0.016631f, 0.999769f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(0.064943f, 0.714049f, 0.696873f, 0.016843f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.615034f, -0.348903f, 0.348903f, 0.615034f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.858806f, 0.041697f, -0.510496f, -0.010359f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.289180f, 0.634787f, -0.620598f, 0.358161f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.636622f, -0.307754f, -0.307754f, 0.636622f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.997048f, -0.064700f, 0.039540f, 0.012063f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
	}

	void Clip::privSetSideStepAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000500f, -0.020833f, 0.007737f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273342f, 0.650441f, 0.641298f, 0.301576f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480434f, -0.518829f, 0.518829f, 0.480434f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.926996f, 0.010783f, -0.374829f, -0.008046f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142469f, 0.693114f, -0.668960f, 0.227570f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571355f, -0.416597f, -0.416598f, 0.571355f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939128f, -0.065612f, -0.336303f, 0.025158f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds
		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025448f, 0.000512f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.006511f, 0.032121f, 0.999463f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.290959f, 0.648355f, 0.685019f, 0.160397f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.580374f, -0.403938f, 0.403938f, 0.580374f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.954554f, -0.121046f, -0.269260f, 0.040919f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.357349f, -0.621459f, 0.683428f, -0.137903f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.550737f, -0.443496f, -0.443496f, 0.550737f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.944544f, 0.117710f, -0.301715f, -0.054299f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025341f, 0.000000f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.010445f, 0.024857f, 0.999636f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.285361f, 0.650265f, 0.680203f, 0.181793f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.567549f, -0.421768f, 0.421768f, 0.567549f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.953107f, -0.094770f, -0.285300f, 0.034784f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.360687f, -0.619753f, 0.682285f, -0.142473f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.541921f, -0.454227f, -0.454228f, 0.541920f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.940785f, 0.122704f, -0.310497f, -0.058816f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025448f, -0.000560f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.013914f, 0.016525f, 0.999767f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273925f, 0.654244f, 0.676136f, 0.199425f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.560788f, -0.430717f, 0.430717f, 0.560788f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.953152f, -0.066619f, -0.293952f, 0.025602f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.362721f, -0.618586f, 0.680238f, -0.151862f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.530955f, -0.466997f, -0.466998f, 0.530955f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.936672f, 0.124434f, -0.321397f, -0.062171f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025762f, -0.001097f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.016191f, 0.008019f, 0.999837f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.257749f, 0.659775f, 0.673108f, 0.212576f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.560894f, -0.430579f, 0.430579f, 0.560893f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.954734f, -0.038499f, -0.294580f, 0.014960f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.361508f, -0.618876f, 0.677436f, -0.165486f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.520195f, -0.478954f, -0.478955f, 0.520195f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933246f, 0.121538f, -0.332182f, -0.062736f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026241f, -0.001578f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.016961f, -0.000000f, 0.999856f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.238300f, 0.666170f, 0.671135f, 0.221377f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.567130f, -0.422331f, 0.422332f, 0.567129f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.957582f, -0.011620f, -0.287891f, 0.004529f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.354621f, -0.621737f, 0.674576f, -0.180649f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.513750f, -0.485861f, -0.485862f, 0.513749f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.931932f, 0.114061f, -0.339077f, -0.059323f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026785f, -0.001981f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.016191f, -0.008255f, 0.999835f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.218880f, 0.672212f, 0.669938f, 0.226726f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.576588f, -0.409324f, 0.409324f, 0.576588f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.960797f, 0.013317f, -0.276896f, -0.004403f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.340436f, -0.627775f, 0.672178f, -0.195392f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.514491f, -0.485076f, -0.485077f, 0.514491f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933531f, 0.103045f, -0.339410f, -0.051991f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027264f, -0.002291f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.013916f, -0.016871f, 0.999761f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.202445f, 0.676990f, 0.668855f, 0.230938f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.585816f, -0.396004f, 0.396004f, 0.585816f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.963358f, 0.036014f, -0.265541f, -0.011502f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.320526f, -0.636001f, 0.670165f, -0.208913f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.521747f, -0.477263f, -0.477264f, 0.521746f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.937519f, 0.089789f, -0.333472f, -0.042330f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027579f, -0.002492f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.010448f, -0.025197f, 0.999628f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.190423f, 0.680117f, 0.667272f, 0.236492f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.592324f, -0.386202f, 0.386203f, 0.592324f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.964590f, 0.056394f, -0.257076f, -0.017257f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.297545f, -0.644941f, 0.667592f, -0.223247f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.531547f, -0.466324f, -0.466324f, 0.531546f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.942421f, 0.073500f, -0.324720f, -0.031568f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027685f, -0.002563f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.006514f, -0.032376f, 0.999454f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.182751f, 0.681822f, 0.664733f, 0.244642f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.595048f, -0.381992f, 0.381992f, 0.595048f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.964290f, 0.074472f, -0.253193f, -0.022168f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.272871f, -0.653749f, 0.663590f, -0.240421f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.540644f, -0.455746f, -0.455747f, 0.540643f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.947015f, 0.052588f, -0.316219f, -0.020060f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027568f, -0.002500f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.003046f, -0.037672f, 0.999286f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.178498f, 0.682516f, 0.660940f, 0.255868f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.593618f, -0.384210f, 0.384210f, 0.593618f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.962443f, 0.090457f, -0.254562f, -0.026803f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.247078f, 0.662016f, -0.658238f, 0.259634f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.548323f, -0.446478f, -0.446478f, 0.548322f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.950754f, 0.027240f, -0.308640f, -0.008182f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027222f, -0.002313f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000769f, -0.040762f, 0.999169f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.176618f, 0.682265f, 0.655899f, 0.270403f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.587848f, -0.392983f, 0.392983f, 0.587847f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.959040f, 0.104647f, -0.261266f, -0.032114f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.220450f, 0.669487f, -0.651832f, 0.279828f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.554479f, -0.438809f, -0.438809f, 0.554479f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.953269f, -0.001812f, -0.302092f, 0.003958f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026696f, -0.002007f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, -0.000000f, -0.041730f, 0.999129f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.175823f, 0.681428f, 0.649853f, 0.287111f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.578662f, -0.406386f, 0.406387f, 0.578662f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.954435f, 0.117160f, -0.271770f, -0.038329f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.192374f, 0.676249f, -0.645009f, 0.299403f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.560355f, -0.431280f, -0.431281f, 0.560354f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.954702f, -0.033637f, -0.295202f, 0.016350f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026098f, -0.001595f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000919f, -0.040810f, 0.999167f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.174158f, 0.680658f, 0.643598f, 0.303569f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.568406f, -0.420612f, 0.420613f, 0.568406f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.949483f, 0.127959f, -0.282980f, -0.045071f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.161775f, 0.682592f, -0.638953f, 0.315651f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.568283f, -0.420779f, -0.420779f, 0.568282f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.955688f, -0.066836f, -0.285283f, 0.028392f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025571f, -0.001101f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.003639f, -0.037840f, 0.999277f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.169216f, 0.680791f, 0.638241f, 0.317076f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.560317f, -0.431330f, 0.431330f, 0.560316f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.945391f, 0.136886f, -0.291283f, -0.051493f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.128576f, 0.688589f, -0.635001f, 0.325710f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.579924f, -0.404585f, -0.404585f, 0.579923f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.956827f, -0.099727f, -0.270236f, 0.038846f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025225f, -0.000556f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.007783f, -0.032687f, 0.999435f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.197216f, 0.674136f, 0.640065f, 0.311390f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542023f, -0.454105f, 0.454105f, 0.542023f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.942725f, 0.107885f, -0.312496f, -0.044459f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.141983f, 0.686138f, -0.634793f, 0.325718f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.568401f, -0.420619f, -0.420620f, 0.568400f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.953382f, -0.094614f, -0.283802f, 0.039581f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025108f, 0.000000f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.012483f, -0.025608f, 0.999594f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.223275f, 0.667256f, 0.642942f, 0.302561f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.525788f, -0.472808f, 0.472808f, 0.525787f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.940044f, 0.076861f, -0.330520f, -0.034141f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.152916f, 0.684527f, -0.636990f, 0.319818f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.561465f, -0.429834f, -0.429834f, 0.561465f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.951499f, -0.089329f, -0.291842f, 0.038707f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025198f, 0.000537f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.016626f, -0.017286f, 0.999712f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.247748f, 0.660124f, 0.646440f, 0.291500f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.512164f, -0.487533f, 0.487533f, 0.512164f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.937304f, 0.044944f, -0.344961f, -0.021039f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.162511f, 0.683363f, -0.641037f, 0.309315f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.558760f, -0.433344f, -0.433345f, 0.558760f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.951107f, -0.083350f, -0.295182f, 0.036261f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025465f, 0.001039f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.019345f, -0.008538f, 0.999776f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.270454f, 0.652932f, 0.650441f, 0.278319f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.502423f, -0.497566f, 0.497566f, 0.502422f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.934854f, 0.013060f, -0.354742f, -0.005945f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.171232f, 0.682368f, -0.646309f, 0.295531f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.559944f, -0.431813f, -0.431814f, 0.559944f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.952098f, -0.076431f, -0.294303f, 0.032456f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025885f, 0.001489f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.020264f, 0.000000f, 0.999795f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.289757f, 0.646470f, 0.655063f, 0.262698f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.498726f, -0.501271f, 0.501271f, 0.498726f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.933485f, -0.017611f, -0.358054f, 0.009637f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.179250f, 0.681401f, -0.652390f, 0.279192f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.564719f, -0.425550f, -0.425550f, 0.564718f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.954368f, -0.068240f, -0.289423f, 0.027536f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026397f, 0.001870f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.019561f, 0.008302f, 0.999774f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.303584f, 0.641766f, 0.660215f, 0.245131f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.502251f, -0.497739f, 0.497739f, 0.502251f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.933794f, -0.045842f, -0.354071f, 0.023670f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.187371f, 0.680171f, -0.658814f, 0.261198f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.571722f, -0.416093f, -0.416094f, 0.571722f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.957416f, -0.058626f, -0.281839f, 0.022001f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026909f, 0.002173f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.017462f, 0.016430f, 0.999713f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.311126f, 0.639345f, 0.665537f, 0.226934f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.512250f, -0.487443f, 0.487443f, 0.512249f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935807f, -0.070688f, -0.343624f, 0.034512f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.196958f, 0.678216f, -0.664962f, 0.243014f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.578891f, -0.406060f, -0.406061f, 0.578891f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.960485f, -0.047552f, -0.273752f, 0.016362f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027329f, 0.002390f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.014158f, 0.023999f, 0.999612f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.313380f, 0.638919f, 0.670635f, 0.209343f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.526509f, -0.472005f, 0.472005f, 0.526509f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.939037f, -0.091730f, -0.328731f, 0.041611f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.209126f, 0.675155f, -0.670220f, 0.226357f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.584358f, -0.398152f, -0.398153f, 0.584358f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.962889f, -0.035001f, -0.267397f, 0.010894f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027596f, 0.002520f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.010133f, 0.030547f, 0.999482f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.312881f, 0.639511f, 0.675542f, 0.191763f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542774f, -0.453207f, 0.453208f, 0.542773f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.942753f, -0.110460f, -0.311289f, 0.045987f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.224292f, -0.670829f, 0.674284f, -0.212184f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.587003f, -0.394244f, -0.394244f, 0.587002f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.964200f, -0.020938f, -0.264288f, 0.005543f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027685f, 0.002563f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.006107f, 0.035674f, 0.999345f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.311415f, 0.640404f, 0.680297f, 0.173491f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.559368f, -0.432559f, 0.432560f, 0.559367f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.946351f, -0.127953f, -0.292720f, 0.048601f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.242064f, -0.665323f, 0.677182f, -0.200439f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.586573f, -0.394882f, -0.394883f, 0.586573f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.964274f, -0.005303f, -0.264855f, 0.000000f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027579f, 0.002489f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.002802f, 0.039186f, 0.999228f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.309081f, 0.641531f, 0.684423f, 0.156435f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.574323f, -0.412496f, 0.412496f, 0.574323f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.949468f, -0.142540f, -0.275203f, 0.049554f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.262480f, -0.658549f, 0.679127f, -0.190274f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.582925f, -0.400248f, -0.400249f, 0.582924f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.962969f, 0.012584f, -0.269241f, -0.006395f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.027264f, 0.002279f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000703f, 0.041137f, 0.999153f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.306241f, 0.642746f, 0.687435f, 0.143272f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.585621f, -0.396292f, 0.396293f, 0.585621f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.951842f, -0.152399f, -0.261419f, 0.049315f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.285570f, -0.650370f, 0.680315f, -0.180665f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.576101f, -0.410009f, -0.410010f, 0.576101f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.960145f, 0.033234f, -0.277147f, -0.014395f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026785f, 0.001953f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, -0.000000f, 0.041731f, 0.999129f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.302692f, 0.644142f, 0.689275f, 0.135493f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.592786f, -0.385494f, 0.385494f, 0.592785f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.953650f, -0.156445f, -0.252479f, 0.048278f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.310090f, -0.641110f, 0.681090f, -0.170111f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.567460f, -0.421887f, -0.421888f, 0.567460f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.956076f, 0.056451f, -0.286594f, -0.024430f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 28  time: 1.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 28 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026241f, 0.001532f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000769f, 0.040729f, 0.999170f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.297700f, 0.646004f, 0.690245f, 0.132719f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.596731f, -0.379358f, 0.379358f, 0.596730f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.955366f, -0.154236f, -0.247653f, 0.046431f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.333346f, -0.631792f, 0.682018f, -0.156752f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.559841f, -0.431947f, -0.431948f, 0.559840f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.951570f, 0.081844f, -0.294110f, -0.036275f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 29  time: 1.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 29 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025762f, 0.001041f, -0.000000f);
		pTmp->poBone[4].Q = Quat(-0.000000f, -0.003046f, 0.037549f, 0.999290f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.290782f, 0.648507f, 0.690771f, 0.133120f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.598866f, -0.375978f, 0.375978f, 0.598866f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.957362f, -0.146227f, -0.245297f, 0.043653f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.351717f, -0.624065f, 0.683699f, -0.139264f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.556708f, -0.435977f, -0.435978f, 0.556708f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.947751f, 0.108616f, -0.295974f, -0.048678f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
	}

	void Clip::privSetShotUpAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000500f, -0.020833f, 0.007737f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273342f, 0.650441f, 0.641298f, 0.301576f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480434f, -0.518829f, 0.518829f, 0.480434f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.926996f, 0.010783f, -0.374829f, -0.008046f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142469f, 0.693114f, -0.668960f, 0.227570f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571355f, -0.416597f, -0.416598f, 0.571355f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939128f, -0.065612f, -0.336303f, 0.025158f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds
		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000000f, -0.353710f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000000f, -0.353710f, -0.000000f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024450f, -0.000680f, -0.000694f);
		pTmp->poBone[4].Q = Quat(-0.000000f, 0.009585f, -0.041201f, 0.999105f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.296936f, 0.643790f, 0.654827f, 0.261849f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.507663f, -0.492218f, 0.492218f, 0.507663f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.931017f, 0.015157f, -0.364646f, -0.003214f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.239704f, 0.663736f, -0.653196f, 0.274466f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.540730f, -0.455643f, -0.455644f, 0.540730f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.943422f, 0.015317f, -0.331224f, -0.003363f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023792f, -0.001678f, -0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.082339f, 0.996604f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.331380f, 0.629103f, 0.648108f, 0.272715f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.478444f, -0.520665f, 0.520665f, 0.478443f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.925587f, 0.038379f, -0.376463f, -0.009578f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.228716f, 0.666456f, -0.648782f, 0.287414f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.544390f, -0.451265f, -0.451265f, 0.544389f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.948979f, 0.038339f, -0.312873f, -0.008925f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023388f, -0.002194f, -0.000008f);
		pTmp->poBone[4].Q = Quat(-0.000110f, -0.010924f, -0.082060f, 0.996567f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.320024f, 0.633417f, 0.646554f, 0.279884f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.470061f, -0.528245f, 0.528246f, 0.470060f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.921831f, 0.049866f, -0.383995f, -0.016984f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.236034f, 0.664752f, -0.651874f, 0.278303f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.535831f, -0.461395f, -0.461396f, 0.535830f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.945535f, 0.049048f, -0.321487f, -0.014259f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022987f, -0.002645f, -0.000034f);
		pTmp->poBone[4].Q = Quat(-0.000440f, -0.023709f, -0.080956f, 0.996436f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.307009f, 0.638433f, 0.645706f, 0.284979f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.462173f, -0.535160f, 0.535161f, 0.462172f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.917999f, 0.060052f, -0.391252f, -0.024353f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.241671f, 0.663506f, -0.655449f, 0.267847f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.527062f, -0.471387f, -0.471388f, 0.527061f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.941811f, 0.058538f, -0.330419f, -0.019701f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022607f, -0.003015f, -0.000083f);
		pTmp->poBone[4].Q = Quat(-0.000959f, -0.037524f, -0.078612f, 0.996198f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.292657f, 0.643972f, 0.645492f, 0.288083f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.455229f, -0.541079f, 0.541079f, 0.455229f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.914289f, 0.068436f, -0.398010f, -0.031316f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.245940f, 0.662594f, -0.659334f, 0.256438f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.518211f, -0.481100f, -0.481101f, 0.518210f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.937852f, 0.066357f, -0.339710f, -0.025030f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022274f, -0.003291f, -0.000157f);
		pTmp->poBone[4].Q = Quat(-0.001590f, -0.051076f, -0.074614f, 0.995902f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.277526f, 0.649746f, 0.645721f, 0.289575f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.449809f, -0.545593f, 0.545594f, 0.449809f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.910974f, 0.074623f, -0.403927f, -0.037418f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.249436f, -0.661794f, 0.663286f, -0.244666f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.509541f, -0.490273f, -0.490273f, 0.509541f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933758f, 0.072155f, -0.349274f, -0.029963f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022010f, -0.003474f, -0.000257f);
		pTmp->poBone[4].Q = Quat(-0.002222f, -0.062890f, -0.068687f, 0.995652f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.262290f, 0.655420f, 0.646104f, 0.290135f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.446459f, -0.548338f, 0.548338f, 0.446459f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.908341f, 0.078521f, -0.408613f, -0.042279f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.252980f, -0.660816f, 0.667045f, -0.233182f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.501396f, -0.498601f, -0.498601f, 0.501395f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.929662f, 0.075861f, -0.358887f, -0.034253f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021828f, -0.003577f, -0.000376f);
		pTmp->poBone[4].Q = Quat(-0.002740f, -0.071779f, -0.060807f, 0.995561f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.247538f, 0.660716f, 0.646327f, 0.290585f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.445481f, -0.549133f, 0.549133f, 0.445480f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.906580f, 0.080405f, -0.411768f, -0.045758f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.257401f, -0.659379f, 0.670412f, -0.222513f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.494067f, 0.505863f, 0.505864f, -0.494067f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.925694f, 0.077749f, -0.368261f, -0.037803f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021726f, -0.003624f, -0.000509f);
		pTmp->poBone[4].Q = Quat(-0.003070f, -0.077137f, -0.051189f, 0.995701f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.233646f, 0.665466f, 0.646152f, 0.291637f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.446846f, -0.548023f, 0.548023f, 0.446845f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.905744f, 0.080777f, -0.413283f, -0.047963f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.263317f, -0.657279f, 0.673275f, -0.212953f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.487704f, 0.512000f, 0.512001f, -0.487704f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.921940f, 0.078303f, -0.377149f, -0.040676f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021695f, -0.003635f, -0.000650f);
		pTmp->poBone[4].Q = Quat(-0.003182f, -0.078900f, -0.040165f, 0.996068f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.220767f, 0.669608f, 0.645452f, 0.293732f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.450289f, -0.545197f, 0.545197f, 0.450289f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.905763f, 0.080157f, -0.413225f, -0.049136f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.271036f, -0.654412f, 0.675594f, -0.204588f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.482312f, 0.517083f, 0.517084f, -0.482312f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.918438f, 0.078029f, -0.385399f, -0.043026f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021833f, -0.003469f, -0.000825f);
		pTmp->poBone[4].Q = Quat(-0.003132f, -0.077996f, -0.027763f, 0.996562f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.209652f, 0.673193f, 0.646168f, 0.292101f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.457402f, -0.539244f, 0.539244f, 0.457401f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.907280f, 0.075377f, -0.411071f, -0.046709f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.275904f, -0.652535f, 0.677394f, -0.198020f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.479544f, 0.519651f, 0.519652f, -0.479544f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.915867f, 0.073864f, -0.392336f, -0.042483f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022245f, -0.002971f, -0.001061f);
		pTmp->poBone[4].Q = Quat(-0.002978f, -0.075059f, -0.014108f, 0.997075f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.200938f, 0.676307f, 0.650137f, 0.282055f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.470155f, -0.528161f, 0.528161f, 0.470155f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.911060f, 0.063322f, -0.405568f, -0.038413f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.273111f, -0.653547f, 0.678696f, -0.194056f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.481455f, 0.517881f, 0.517882f, -0.481454f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.915038f, 0.062620f, -0.396802f, -0.036513f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022893f, -0.002189f, -0.001341f);
		pTmp->poBone[4].Q = Quat(-0.002723f, -0.069993f, -0.000010f, 0.997544f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.193969f, 0.679008f, 0.656563f, 0.265045f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.488276f, -0.511455f, 0.511455f, 0.488276f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.916907f, 0.045551f, -0.395629f, -0.026153f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.263518f, -0.657095f, 0.679524f, -0.192435f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.488337f, 0.511397f, 0.511398f, -0.488337f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.916045f, 0.045556f, -0.397620f, -0.026161f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023683f, -0.001235f, -0.001637f);
		pTmp->poBone[4].Q = Quat(-0.002389f, -0.062986f, 0.013343f, 0.997922f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.187859f, 0.681327f, 0.663977f, 0.244206f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.510129f, -0.489662f, 0.489662f, 0.510128f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.924129f, 0.025048f, -0.381034f, -0.013053f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.249681f, -0.662073f, 0.679942f, -0.192347f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.499475f, 0.500524f, 0.500525f, -0.499475f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.918647f, 0.025440f, -0.394012f, -0.013951f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024473f, -0.000281f, -0.001908f);
		pTmp->poBone[4].Q = Quat(-0.002019f, -0.054566f, 0.024672f, 0.998203f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.182375f, 0.683184f, 0.670739f, 0.223849f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532405f, -0.465344f, 0.465344f, 0.532405f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.931525f, 0.005517f, -0.363629f, -0.002127f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.235465f, -0.666983f, 0.680008f, -0.193077f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.512624f, -0.487049f, -0.487050f, 0.512623f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.922137f, 0.005956f, -0.386808f, -0.002893f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025122f, 0.000501f, -0.002119f);
		pTmp->poBone[4].Q = Quat(-0.001660f, -0.045476f, 0.033012f, 0.998418f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.178431f, 0.684361f, 0.675631f, 0.208171f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.551134f, -0.443002f, 0.443003f, 0.551134f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.937739f, -0.009905f, -0.347161f, 0.005112f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.224678f, -0.670569f, 0.679693f, -0.194613f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.524624f, -0.474099f, -0.474100f, 0.524623f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.925518f, -0.009612f, -0.378549f, 0.005012f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025534f, 0.000999f, -0.002247f);
		pTmp->poBone[4].Q = Quat(-0.001349f, -0.036422f, 0.037943f, 0.998615f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.177538f, 0.684596f, 0.678058f, 0.200113f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.563264f, -0.427473f, 0.427474f, 0.563264f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.941748f, -0.019478f, -0.335640f, 0.008759f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.219840f, -0.672150f, 0.678883f, -0.197492f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532770f, -0.464925f, -0.464926f, 0.532770f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.927912f, -0.019357f, -0.372181f, 0.009288f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025672f, 0.001165f, -0.002289f);
		pTmp->poBone[4].Q = Quat(-0.001104f, -0.027901f, 0.039522f, 0.998828f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.180742f, 0.683703f, 0.677862f, 0.200962f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.567424f, -0.421936f, 0.421936f, 0.567424f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.943088f, -0.022728f, -0.331628f, 0.009575f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.221933f, -0.671508f, 0.677464f, -0.202149f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.535643f, -0.461613f, -0.461614f, 0.535642f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.928823f, -0.022692f, -0.369683f, 0.010339f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025635f, 0.001112f, -0.002248f);
		pTmp->poBone[4].Q = Quat(-0.000887f, -0.020125f, 0.037729f, 0.999085f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.188077f, 0.681628f, 0.676034f, 0.207337f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.565894f, -0.423986f, 0.423987f, 0.565893f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.942672f, -0.021843f, -0.332887f, 0.008843f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.227517f, -0.669715f, 0.675410f, -0.208660f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.535536f, -0.461737f, -0.461737f, 0.535536f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.929203f, -0.021830f, -0.368802f, 0.009529f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025528f, 0.000956f, -0.002128f);
		pTmp->poBone[4].Q = Quat(-0.000660f, -0.013331f, 0.032426f, 0.999385f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.199117f, 0.678383f, 0.673571f, 0.215525f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.561182f, -0.430203f, 0.430203f, 0.561182f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.941516f, -0.018943f, -0.336353f, 0.007427f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.232919f, -0.667907f, 0.672786f, -0.216816f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.535079f, -0.462266f, -0.462267f, 0.535079f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.930114f, -0.018952f, -0.366696f, 0.007929f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025365f, 0.000718f, -0.001943f);
		pTmp->poBone[4].Q = Quat(-0.000439f, -0.007861f, 0.024346f, 0.999673f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.212573f, 0.674227f, 0.670621f, 0.224716f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.554012f, -0.439399f, 0.439399f, 0.554011f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.939844f, -0.014382f, -0.341257f, 0.005497f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.237768f, -0.666191f, 0.669828f, -0.225804f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.534407f, -0.463043f, -0.463043f, 0.534407f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.931441f, -0.014398f, -0.363560f, 0.005779f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025180f, 0.000447f, -0.001734f);
		pTmp->poBone[4].Q = Quat(-0.000248f, -0.003937f, 0.015180f, 0.999877f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.226106f, 0.669822f, 0.667585f, 0.233547f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.545956f, -0.449368f, 0.449369f, 0.545956f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.938060f, -0.009074f, -0.346338f, 0.003403f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.241670f, -0.664721f, 0.666967f, -0.234301f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.533733f, -0.463820f, -0.463821f, 0.533732f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.932923f, -0.009084f, -0.359943f, 0.003512f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025016f, 0.000209f, -0.001550f);
		pTmp->poBone[4].Q = Quat(-0.000107f, -0.001517f, 0.007097f, 0.999974f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.237156f, 0.666056f, 0.665017f, 0.240580f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.538940f, -0.457760f, 0.457760f, 0.538939f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.936582f, -0.004287f, -0.350419f, 0.001586f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.244372f, -0.663640f, 0.664680f, -0.240965f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.533225f, -0.464404f, -0.464404f, 0.533225f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.934221f, -0.004289f, -0.356665f, 0.001610f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024909f, 0.000053f, -0.001429f);
		pTmp->poBone[4].Q = Quat(-0.000025f, -0.000324f, 0.001793f, 0.999998f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.244051f, 0.663629f, 0.663367f, 0.244907f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.534381f, -0.463073f, 0.463074f, 0.534381f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935659f, -0.001090f, -0.352904f, 0.000400f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.245864f, -0.663014f, 0.663275f, -0.245010f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532938f, -0.464733f, -0.464734f, 0.532938f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935069f, -0.001090f, -0.354463f, 0.000402f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(-0.000008f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, 0.000003f, -0.353710f, 0.000008f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246311f, 0.662820f, -0.662820f, 0.246312f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532849f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000003f, -0.353711f, 0.000007f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(-0.000001f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, 0.000000f, -0.353710f, 0.000001f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246312f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532849f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000001f, -0.353711f, 0.000001f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024873f, 0.000000f, -0.001388f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246312f, 0.662820f, 0.662819f, 0.246312f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.532849f, -0.464835f, 0.464836f, 0.532849f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[7].Q = Quat(0.935355f, -0.000000f, -0.353710f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.246312f, 0.662820f, -0.662820f, 0.246313f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532849f, -0.464835f, -0.464836f, 0.532848f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935355f, 0.000000f, -0.353710f, -0.000000f);
		pTmp->poBone[10].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.026428f, 0.001437f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000116f, -0.020830f, 0.007736f, 0.999753f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.273412f, 0.650407f, 0.641251f, 0.301684f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[6].Q = Quat(-0.480448f, -0.518816f, 0.518817f, 0.480447f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.927060f, 0.010960f, -0.374673f, -0.007709f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.142395f, 0.693133f, -0.668972f, 0.227524f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.571363f, -0.416587f, -0.416588f, 0.571362f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939094f, -0.065492f, -0.336395f, 0.025523f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

	}

	void Clip::privSetTurnRightAnimationData()
	{
		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024349f, -0.002596f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.056869f, 0.998382f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.284394f, 0.647176f, 0.646073f, 0.287877f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.503703f, -0.496269f, 0.496270f, 0.503703f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.933769f, 0.055493f, -0.352907f, -0.021277f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.254720f, -0.659635f, 0.659639f, -0.254707f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.549178f, -0.445425f, -0.445426f, 0.549178f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.949887f, 0.054116f, -0.307374f, -0.017513f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.499489f, -0.500510f, 0.499489f, 0.500511f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024116f, -0.001977f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.054948f, 0.998489f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.285456f, 0.648534f, 0.644381f, 0.287563f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.501743f, -0.498250f, 0.498251f, 0.501743f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.932568f, 0.053276f, -0.356383f, -0.021649f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.252951f, 0.660238f, -0.654797f, 0.267101f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.541502f, -0.454726f, -0.454726f, 0.541502f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.947713f, 0.042324f, -0.316042f, -0.012933f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.497942f, -0.502049f, 0.497942f, 0.502049f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023938f, -0.001318f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.051591f, 0.998668f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.288653f, 0.652721f, 0.639140f, 0.286591f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.495808f, -0.504157f, 0.504158f, 0.495807f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.928756f, 0.048916f, -0.366693f, -0.023566f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.250442f, 0.662618f, -0.648990f, 0.277540f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.534756f, -0.462640f, -0.462641f, 0.534756f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.945508f, 0.029352f, -0.324182f, -0.007614f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.495334f, -0.504623f, 0.495334f, 0.504623f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023829f, -0.000643f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.046766f, 0.998906f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.293820f, 0.659684f, 0.630320f, 0.284928f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.486114f, -0.513511f, 0.513511f, 0.486113f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.922368f, 0.042294f, -0.383028f, -0.027176f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.247319f, 0.666816f, -0.642496f, 0.285287f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.529354f, -0.468812f, -0.468813f, 0.529353f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.943280f, 0.015707f, -0.331620f, -0.001838f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.491629f, -0.508233f, 0.491629f, 0.508233f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023792f, 0.000000f, 0.000000f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.040573f, 0.999177f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.300450f, 0.668968f, 0.618338f, 0.282612f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.473504f, -0.525161f, 0.525161f, 0.473504f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.913814f, 0.033178f, -0.403415f, -0.033146f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.244181f, 0.672689f, -0.635657f, 0.289491f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.525490f, -0.473139f, -0.473140f, 0.525489f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.940992f, 0.002462f, -0.338398f, 0.003864f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.486786f, -0.512873f, 0.486786f, 0.512873f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023837f, 0.000720f, 0.000024f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.033263f, 0.999447f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.307698f, 0.679699f, 0.604189f, 0.279798f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.459573f, -0.537394f, 0.537395f, 0.459573f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.904030f, 0.021187f, -0.424804f, -0.042691f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.239342f, 0.680551f, -0.627947f, 0.291973f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.523516f, -0.475322f, -0.475323f, 0.523515f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.938839f, -0.012372f, -0.343972f, 0.010539f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.480759f, -0.518527f, 0.480759f, 0.518527f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023972f, 0.001470f, 0.000095f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.025193f, 0.999683f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.314584f, 0.690786f, 0.589294f, 0.276740f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.446383f, -0.548400f, 0.548400f, 0.446382f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.894287f, 0.005900f, -0.443781f, -0.057217f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.233342f, 0.690081f, -0.619629f, 0.292232f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.523923f, -0.474874f, -0.474874f, 0.523922f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.937090f, -0.027607f, -0.347542f, 0.017730f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.473497f, -0.525167f, 0.473497f, 0.525167f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024189f, 0.002189f, 0.000214f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.016752f, 0.999860f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.320281f, 0.701252f, 0.575099f, 0.273728f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.435842f, -0.556814f, 0.556814f, 0.435842f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.885706f, -0.012808f, -0.457520f, -0.077692f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.226938f, 0.700842f, -0.611051f, 0.289718f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.526593f, -0.471911f, -0.471912f, 0.526592f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.935744f, -0.041772f, -0.349311f, 0.024916f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.464946f, -0.532752f, 0.464946f, 0.532752f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024464f, 0.002849f, 0.000381f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.008273f, 0.999966f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.324300f, 0.710465f, 0.562696f, 0.271003f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.429207f, -0.561944f, 0.561945f, 0.429207f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.878846f, -0.034390f, -0.464334f, -0.104118f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.220626f, 0.712367f, -0.602334f, 0.284694f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.530967f, -0.466983f, -0.466984f, 0.530967f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.934689f, -0.054074f, -0.349860f, 0.032088f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.455056f, -0.541224f, 0.455056f, 0.541224f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024761f, 0.003432f, 0.000592f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.326476f, 0.718145f, 0.552697f, 0.268716f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.426984f, -0.563635f, 0.563636f, 0.426984f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.873715f, -0.057503f, -0.463664f, -0.135391f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.214997f, 0.724101f, -0.593506f, 0.277858f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.536094f, -0.461089f, -0.461090f, 0.536093f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.933674f, -0.063982f, -0.350134f, 0.039574f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.443781f, -0.550508f, 0.443781f, 0.550508f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025037f, 0.003920f, 0.000843f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.007893f, 0.999969f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.325264f, 0.726351f, 0.544567f, 0.264698f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.429843f, -0.561458f, 0.561458f, 0.429843f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.869703f, -0.079488f, -0.457392f, -0.167603f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.210727f, 0.735454f, -0.584595f, 0.270093f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.540847f, -0.455504f, -0.455505f, 0.540847f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.932346f, -0.071104f, -0.351253f, 0.047925f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.431084f, -0.560506f, 0.431084f, 0.560506f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025253f, 0.004296f, 0.001128f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.016529f, 0.999863f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.319038f, 0.737059f, 0.537647f, 0.256700f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.438400f, -0.554802f, 0.554803f, 0.438400f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.867126f, -0.098900f, -0.447115f, -0.195960f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.209717f, 0.745557f, -0.575869f, 0.261797f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.543748f, -0.452037f, -0.452038f, 0.543748f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.930146f, -0.075129f, -0.354746f, 0.057787f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.416947f, -0.571100f, 0.416947f, 0.571100f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025388f, 0.004540f, 0.001440f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.025551f, 0.999673f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.307986f, 0.749768f, 0.531969f, 0.244951f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.452144f, -0.543660f, 0.543660f, 0.452144f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.866730f, -0.114407f, -0.433536f, -0.218485f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.212233f, 0.754013f, -0.567573f, 0.253539f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.544246f, -0.451438f, -0.451438f, 0.544246f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.926844f, -0.075603f, -0.361095f, 0.069680f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.401372f, -0.582152f, 0.401372f, 0.582152f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025433f, 0.004627f, 0.001767f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.034412f, 0.999408f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.292906f, 0.763543f, 0.527465f, 0.230194f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.469761f, -0.528511f, 0.528512f, 0.469761f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.868919f, -0.125267f, -0.417842f, -0.233872f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.218164f, 0.760564f, -0.560044f, 0.245556f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.542206f, -0.453886f, -0.453887f, 0.542206f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.922361f, -0.071948f, -0.370188f, 0.083867f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.384389f, -0.593502f, 0.384389f, 0.593503f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025397f, 0.004570f, 0.002101f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.042445f, 0.999099f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.275348f, 0.777119f, 0.523991f, 0.213784f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.489154f, -0.510616f, 0.510616f, 0.489154f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.873531f, -0.131385f, -0.401681f, -0.241526f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.226263f, 0.765316f, -0.553556f, 0.238057f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.538120f, -0.458723f, -0.458724f, 0.538119f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.916723f, -0.064244f, -0.381289f, 0.100552f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.366061f, -0.604979f, 0.366061f, 0.604979f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025287f, 0.004399f, 0.002429f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.049039f, 0.998797f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.257447f, 0.789214f, 0.521387f, 0.197531f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.507865f, -0.492009f, 0.492010f, 0.507865f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.879920f, -0.133134f, -0.386959f, -0.241413f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.234914f, 0.768576f, -0.548263f, 0.231331f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.532579f, -0.465145f, -0.465145f, 0.532579f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.909869f, -0.052957f, -0.393659f, 0.119858f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.346491f, -0.616396f, 0.346491f, 0.616396f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025109f, 0.004117f, 0.002740f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.053796f, 0.998552f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241436f, 0.798885f, 0.519521f, 0.183272f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.523753f, -0.475061f, 0.475062f, 0.523753f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.887257f, -0.131030f, -0.375428f, -0.233797f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.243348f, 0.770502f, -0.544356f, 0.225357f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.525898f, -0.472685f, -0.472686f, 0.525898f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.901725f, -0.038053f, -0.406700f, 0.141559f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.325820f, -0.627568f, 0.325820f, 0.627568f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024876f, 0.003728f, 0.003026f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.056584f, 0.998398f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.229090f, 0.805698f, 0.518303f, 0.172425f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535469f, -0.461815f, 0.461815f, 0.535469f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.894793f, -0.125457f, -0.368276f, -0.219040f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.250933f, 0.771277f, -0.542027f, 0.219933f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.518523f, -0.480764f, -0.480765f, 0.518522f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.892285f, -0.019613f, -0.419665f, 0.165301f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.304229f, -0.638314f, 0.304229f, 0.638314f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024613f, 0.003242f, 0.003277f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.057474f, 0.998347f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.221458f, 0.809635f, 0.517651f, 0.165784f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542476f, -0.453563f, 0.453563f, 0.542476f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.901928f, -0.116563f, -0.365967f, -0.197503f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.257118f, 0.771107f, -0.541459f, 0.214724f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.511076f, -0.488673f, -0.488673f, 0.511076f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.881666f, 0.002113f, -0.431638f, 0.190655f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.281934f, -0.648470f, 0.281934f, 0.648470f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024349f, 0.002673f, 0.003488f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.056877f, 0.998381f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.235120f, 0.806083f, 0.517074f, 0.166083f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.544763f, -0.450813f, 0.450814f, 0.544763f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.914032f, -0.108344f, -0.352644f, -0.168670f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.261611f, 0.770128f, -0.542819f, 0.209308f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.504229f, -0.495735f, -0.495735f, 0.504229f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.870051f, 0.026657f, -0.441719f, 0.217221f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.259181f, -0.657895f, 0.259181f, 0.657895f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024116f, 0.002039f, 0.003654f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.054974f, 0.998488f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.244757f, 0.802892f, 0.511473f, 0.183992f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.537564f, -0.459375f, 0.459376f, 0.537563f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.919608f, -0.085098f, -0.356194f, -0.142149f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.262991f, 0.768950f, -0.543229f, 0.210840f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.498670f, 0.501327f, 0.501327f, -0.498669f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.859237f, 0.044346f, -0.447420f, 0.244050f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.236234f, -0.666478f, 0.236234f, 0.666478f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023938f, 0.001364f, 0.003773f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.051637f, 0.998666f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.252299f, 0.798652f, 0.507666f, 0.201931f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.531569f, -0.466298f, 0.466299f, 0.531569f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.924084f, -0.061187f, -0.358124f, -0.118624f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.267126f, 0.765313f, -0.544531f, 0.215468f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.491309f, 0.508543f, 0.508543f, -0.491308f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.850005f, 0.060440f, -0.451132f, 0.265178f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.213368f, -0.674147f, 0.213368f, 0.674147f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023829f, 0.000675f, 0.003845f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.046824f, 0.998903f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.257875f, 0.793340f, 0.506006f, 0.219250f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.527145f, -0.471294f, 0.471294f, 0.527145f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.927827f, -0.037414f, -0.357913f, -0.098164f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.273799f, 0.759151f, -0.546791f, 0.223032f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.482309f, 0.517087f, 0.517087f, -0.482308f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.843037f, 0.074604f, -0.452950f, 0.280284f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.190851f, -0.680864f, 0.190851f, 0.680864f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023792f, 0.000000f, 0.003868f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.040632f, 0.999174f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.261793f, 0.786915f, 0.506792f, 0.235353f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.524442f, -0.474300f, 0.474301f, 0.524441f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.931138f, -0.014702f, -0.355331f, -0.080657f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.282427f, 0.750633f, -0.550001f, 0.232986f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.472106f, 0.526418f, 0.526418f, -0.472105f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.838907f, 0.086472f, -0.453108f, 0.288878f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.168940f, -0.686629f, 0.168940f, 0.686629f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023829f, -0.000675f, 0.003847f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.033313f, 0.999445f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.263638f, 0.779605f, 0.510003f, 0.250215f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.523511f, -0.475328f, 0.475328f, 0.523510f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.934133f, 0.006846f, -0.350665f, -0.066200f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.292039f, 0.740277f, -0.554068f, 0.244360f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.461454f, 0.535780f, 0.535781f, -0.461453f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.837998f, 0.095616f, -0.452033f, 0.290317f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.147866f, -0.691474f, 0.147866f, 0.691474f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023938f, -0.001364f, 0.003783f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.025235f, 0.999682f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.262881f, 0.771704f, 0.515557f, 0.263756f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.524482f, -0.474256f, 0.474257f, 0.524481f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.936940f, 0.027207f, -0.344091f, -0.054817f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.301418f, 0.728952f, -0.558836f, 0.255887f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.451320f, 0.544344f, 0.544344f, -0.451320f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.840394f, 0.101573f, -0.450328f, 0.283944f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.127830f, -0.695456f, 0.127830f, 0.695456f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024116f, -0.002039f, 0.003675f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.016784f, 0.999859f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.259868f, 0.763269f, 0.523472f, 0.275439f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.527311f, -0.471108f, 0.471109f, 0.527311f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.939750f, 0.045615f, -0.335653f, -0.046115f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.309401f, 0.717708f, -0.564135f, 0.266304f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.442664f, 0.551406f, 0.551407f, -0.442663f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.845786f, 0.103952f, -0.448644f, 0.269368f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.109002f, -0.698655f, 0.109002f, 0.698655f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024349f, -0.002673f, 0.003524f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, 0.008293f, 0.999966f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.255194f, 0.754324f, 0.533567f, 0.284917f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.531648f, -0.466208f, 0.466209f, 0.531648f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.942612f, 0.061466f, -0.325777f, -0.039678f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.315136f, 0.707507f, -0.569818f, 0.274647f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.436199f, 0.556535f, 0.556535f, -0.436198f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.853429f, 0.102595f, -0.447486f, 0.246758f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 28  time: 1.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 28 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.091515f, -0.701160f, 0.091515f, 0.701160f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024613f, -0.003242f, 0.003333f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.249667f, 0.744873f, 0.545428f, 0.292128f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.536825f, -0.460237f, 0.460238f, 0.536825f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.945426f, 0.074408f, -0.315278f, -0.035129f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.318178f, 0.699032f, -0.575770f, 0.280367f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.432295f, 0.559573f, 0.559573f, -0.432294f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.862245f, 0.097707f, -0.447081f, 0.217039f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 29  time: 1.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 29 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.075467f, -0.703068f, 0.075467f, 0.703068f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024876f, -0.003728f, 0.003105f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.008293f, 0.999966f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.244560f, 0.734825f, 0.558478f, 0.297196f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.541836f, -0.454327f, 0.454328f, 0.541836f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.947942f, 0.084378f, -0.305373f, -0.032159f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.318422f, 0.692639f, -0.581902f, 0.283282f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.431016f, 0.560558f, 0.560558f, -0.431016f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.871095f, 0.090162f, -0.447258f, 0.181727f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 30  time: 1.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 30 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.060930f, -0.704477f, 0.060930f, 0.704477f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025109f, -0.004117f, 0.002844f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.016784f, 0.999859f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241008f, 0.724176f, 0.572029f, 0.300446f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.545703f, -0.449676f, 0.449676f, 0.545703f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.949900f, 0.091519f, -0.297295f, -0.030497f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.316144f, 0.687335f, -0.589002f, 0.284076f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.433918f, 0.558315f, 0.558315f, -0.433918f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.880361f, 0.081429f, -0.444425f, 0.144289f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 31  time: 1.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 31 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.047946f, -0.705479f, 0.047946f, 0.705479f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025287f, -0.004399f, 0.002556f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.025235f, 0.999682f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.239459f, 0.713148f, 0.585371f, 0.302356f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.547825f, -0.447088f, 0.447088f, 0.547825f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.951151f, 0.096048f, -0.291883f, -0.029857f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.311568f, 0.682077f, -0.597819f, 0.283388f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.442600f, 0.551457f, 0.551458f, -0.442600f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.890858f, 0.073157f, -0.435046f, 0.108418f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 32  time: 1.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 32 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.036536f, -0.706162f, 0.036536f, 0.706162f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025397f, -0.004570f, 0.002250f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.033313f, 0.999445f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.240002f, 0.702061f, 0.597908f, 0.303340f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.547926f, -0.446964f, 0.446965f, 0.547926f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.951630f, 0.098199f, -0.289590f, -0.029907f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.304845f, 0.676954f, -0.608031f, 0.281249f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.456535f, 0.539978f, 0.539978f, -0.456534f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.902180f, 0.066503f, -0.419357f, 0.076081f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 33  time: 1.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 33 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.026706f, -0.706602f, 0.026706f, 0.706602f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025433f, -0.004627f, 0.001934f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.040632f, 0.999174f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.242457f, 0.691280f, 0.609194f, 0.303692f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.546010f, -0.449302f, 0.449303f, 0.546010f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.951348f, 0.098179f, -0.290485f, -0.030284f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.296427f, 0.672096f, -0.619041f, 0.277861f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.474376f, 0.524373f, 0.524374f, -0.474376f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.913790f, 0.061953f, -0.398477f, 0.048635f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 34  time: 1.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 34 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.018447f, -0.706866f, 0.018447f, 0.706866f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025397f, -0.004557f, 0.001618f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.046824f, 0.998903f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246806f, 0.681078f, 0.618980f, 0.303454f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542172f, -0.453926f, 0.453927f, 0.542172f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.950355f, 0.095886f, -0.294448f, -0.030520f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.287101f, 0.667673f, -0.630006f, 0.273638f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(-0.493986f, 0.505942f, 0.505943f, -0.493986f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.924927f, 0.059315f, -0.374541f, 0.026649f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 35  time: 1.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 35 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.011741f, -0.707009f, 0.011741f, 0.707009f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025287f, -0.004360f, 0.001312f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.051637f, 0.998666f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.252934f, 0.671680f, 0.627086f, 0.302709f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.536542f, -0.460568f, 0.460569f, 0.536541f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.948672f, 0.091390f, -0.301255f, -0.030250f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.277895f, 0.663878f, -0.639994f, 0.269163f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.512873f, -0.486786f, -0.486787f, 0.512873f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.934736f, 0.057969f, -0.350441f, 0.009946f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 36  time: 1.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 36 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.006569f, -0.707076f, 0.006569f, 0.707076f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.025109f, -0.004051f, 0.001025f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.054974f, 0.998488f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.260514f, 0.663316f, 0.633426f, 0.301521f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.529410f, -0.468749f, 0.468749f, 0.529410f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.946330f, 0.085009f, -0.310446f, -0.029243f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.269834f, 0.660875f, -0.648211f, 0.265059f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.528883f, -0.469343f, -0.469344f, 0.528882f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.942551f, 0.057221f, -0.329117f, -0.002089f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 37  time: 1.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 37 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.002904f, -0.707101f, 0.002904f, 0.707101f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024876f, -0.003646f, 0.000764f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.056877f, 0.998381f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.269292f, 0.656155f, 0.638073f, 0.299676f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.521236f, -0.477821f, 0.477821f, 0.521236f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.943435f, 0.076950f, -0.321349f, -0.027265f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.263706f, 0.658760f, -0.654167f, 0.261839f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.540673f, -0.455711f, -0.455712f, 0.540673f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.948069f, 0.056571f, -0.312830f, -0.010135f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 38  time: 1.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 38 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.000722f, -0.707106f, 0.000722f, 0.707106f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024613f, -0.003156f, 0.000535f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.057474f, 0.998347f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.278997f, 0.650337f, 0.641228f, 0.296731f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.512692f, -0.486978f, 0.486978f, 0.512691f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.940182f, 0.067336f, -0.333082f, -0.024104f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.259955f, -0.657541f, 0.657688f, -0.259824f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.547722f, -0.447214f, -0.447215f, 0.547722f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.951296f, 0.055774f, -0.302835f, -0.014680f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 39  time: 1.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 39 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.000000f, -0.707107f, 0.000000f, 0.707107f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.024349f, -0.002596f, 0.000344f);
		pTmp->poBone[4].Q = Quat(0.000000f, 0.000000f, -0.056869f, 0.998382f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.289239f, 0.646016f, 0.643150f, 0.292168f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.504631f, -0.495325f, 0.495326f, 0.504631f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.936855f, 0.056267f, -0.344602f, -0.019634f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.258713f, -0.657157f, 0.658828f, -0.259147f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, 0.000000f);
		pTmp->poBone[9].Q = Quat(0.550029f, -0.444374f, -0.444374f, 0.550029f);
		pTmp->poBone[9].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[10].Q = Quat(0.952381f, 0.054754f, -0.299528f, -0.015948f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 0.999999f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

	}

	void Clip::privSetDieLeftAnimationData()
	{

		// --------  Frame 0  ----------------------------

		FrameBucket* pTmp = nullptr;
		FrameBucket* pTmpX = nullptr;

		// Keyframe: 0  time: 0.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 0 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		//pTmp->nextBucket = pTmpX;
		this->poHead = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023792f, 0.000000f, -0.002410f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.000000f, -0.000000f, 1.000000f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.247495f, 0.662379f, 0.662379f, 0.247496f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.507033f, -0.492866f, 0.492867f, 0.507033f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.915661f, 0.000000f, -0.401952f, 0.000000f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.247495f, 0.662379f, -0.662379f, 0.247496f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.507033f, -0.492866f, -0.492867f, 0.507033f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.915661f, 0.000000f, -0.401952f, 0.000000f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 1  time: 0.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 1 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023785f, 0.000156f, -0.002526f);
		pTmp->poBone[4].Q = Quat(-0.000077f, 0.000720f, 0.001951f, 0.999998f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.246932f, 0.662654f, 0.663348f, 0.244714f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.507681f, -0.492199f, 0.492200f, 0.507680f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.914878f, -0.003223f, -0.403715f, 0.001595f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.245629f, 0.663079f, -0.662255f, 0.247812f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.506110f, -0.493814f, -0.493815f, 0.506110f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.914137f, -0.003264f, -0.405390f, 0.001520f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 2  time: 0.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 2 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023762f, 0.000623f, -0.002876f);
		pTmp->poBone[4].Q = Quat(-0.000310f, 0.002892f, 0.007837f, 0.999965f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.245062f, 0.663503f, 0.666244f, 0.236276f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.509881f, -0.489920f, 0.489920f, 0.509880f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.912577f, -0.012868f, -0.408653f, 0.006356f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.239837f, 0.665237f, -0.661918f, 0.248599f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.503577f, -0.496397f, -0.496398f, 0.503577f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.909509f, -0.013077f, -0.415432f, 0.006179f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 3  time: 0.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 3 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023725f, 0.001373f, -0.003438f);
		pTmp->poBone[4].Q = Quat(-0.000693f, 0.006458f, 0.017501f, 0.999826f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.241417f, 0.664975f, 0.670821f, 0.222542f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.514258f, -0.485323f, 0.485324f, 0.514258f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.909085f, -0.028261f, -0.415419f, 0.013874f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.230088f, 0.668837f, -0.661473f, 0.249339f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.500217f, -0.499783f, -0.499783f, 0.500217f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.901913f, -0.028890f, -0.430726f, 0.013917f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 4  time: 0.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 4 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023678f, 0.002328f, -0.004153f);
		pTmp->poBone[4].Q = Quat(-0.001204f, 0.011216f, 0.030395f, 0.999474f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.235456f, 0.667089f, 0.676414f, 0.204980f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.521399f, -0.477643f, 0.477644f, 0.521399f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.905142f, -0.047633f, -0.421802f, 0.023082f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.217250f, 0.673541f, -0.661059f, 0.249289f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.497129f, 0.502855f, 0.502856f, -0.497128f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.891985f, -0.049071f, -0.448749f, 0.024082f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 5  time: 0.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 5 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023627f, 0.003358f, -0.004925f);
		pTmp->poBone[4].Q = Quat(-0.001802f, 0.016790f, 0.045500f, 0.998822f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.227012f, 0.669774f, 0.682017f, 0.186336f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.531209f, -0.466709f, 0.466710f, 0.531208f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.901751f, -0.068208f, -0.425611f, 0.032363f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.203523f, 0.678596f, -0.660788f, 0.247882f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.495124f, 0.504829f, 0.504829f, -0.495124f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.880961f, -0.070871f, -0.466523f, 0.035242f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 6  time: 0.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 6 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023580f, 0.004312f, -0.005639f);
		pTmp->poBone[4].Q = Quat(-0.002431f, 0.022652f, 0.061385f, 0.997854f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.216495f, 0.673063f, 0.683783f, 0.180435f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.540129f, -0.456356f, 0.456357f, 0.540128f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.901360f, -0.079681f, -0.424052f, 0.037162f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.191975f, 0.683043f, -0.660689f, 0.245129f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.494190f, 0.505743f, 0.505744f, -0.494189f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.870376f, -0.091057f, -0.481746f, 0.045558f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 7  time: 0.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 7 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023543f, 0.005063f, -0.006201f);
		pTmp->poBone[4].Q = Quat(-0.003028f, 0.028213f, 0.076455f, 0.996669f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.205560f, 0.676573f, 0.678390f, 0.199452f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543623f, -0.452188f, 0.452188f, 0.543623f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.905271f, -0.073308f, -0.417042f, 0.034446f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.185294f, 0.686110f, -0.660701f, 0.241647f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.493556f, 0.506362f, 0.506362f, -0.493556f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.861526f, -0.106918f, -0.493438f, 0.053490f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 8  time: 0.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 8 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023520f, 0.005530f, -0.006551f);
		pTmp->poBone[4].Q = Quat(-0.003536f, 0.032947f, 0.089286f, 0.995455f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.194639f, 0.679336f, 0.666641f, 0.237081f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543024f, -0.452907f, 0.452908f, 0.543024f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.912470f, -0.052319f, -0.404986f, 0.025449f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.184873f, 0.687389f, -0.660708f, 0.238293f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.492301f, 0.507583f, 0.507583f, -0.492300f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.855180f, -0.116872f, -0.501618f, 0.058206f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 9  time: 0.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 9 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023513f, 0.005686f, -0.006668f);
		pTmp->poBone[4].Q = Quat(-0.003915f, 0.036484f, 0.098868f, 0.994424f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.183552f, 0.680584f, 0.652022f, 0.279251f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.542267f, -0.453813f, 0.453814f, 0.542267f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.921068f, -0.025311f, -0.388354f, 0.013211f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.190795f, 0.686744f, -0.660614f, 0.235732f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.489879f, 0.509920f, 0.509921f, -0.489879f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.851667f, -0.120398f, -0.506587f, 0.059472f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 10  time: 0.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 10 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023522f, 0.005539f, -0.006575f);
		pTmp->poBone[4].Q = Quat(-0.004145f, 0.038622f, 0.104662f, 0.993749f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.173702f, 0.680534f, 0.639492f, 0.312653f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.543178f, -0.452723f, 0.452723f, 0.543178f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.928469f, -0.001671f, -0.371400f, 0.002055f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.201934f, 0.684298f, -0.660492f, 0.233901f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.486447f, 0.513195f, 0.513196f, -0.486446f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.850957f, -0.117674f, -0.508655f, 0.057403f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 11  time: 0.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 11 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023549f, 0.005076f, -0.006279f);
		pTmp->poBone[4].Q = Quat(-0.004218f, 0.039304f, 0.106512f, 0.993525f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.167074f, 0.680034f, 0.631651f, 0.332652f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.544679f, -0.450915f, 0.450916f, 0.544679f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.933281f, 0.014425f, -0.358812f, -0.005624f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.218165f, 0.679764f, -0.660535f, 0.232422f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.482240f, 0.517150f, 0.517151f, -0.482240f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.853187f, -0.108292f, -0.507600f, 0.051844f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 12  time: 0.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 12 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023592f, 0.004282f, -0.005767f);
		pTmp->poBone[4].Q = Quat(-0.003954f, 0.035534f, 0.104020f, 0.993932f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.161131f, 0.679774f, 0.626240f, 0.346075f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.545766f, -0.449599f, 0.449599f, 0.545766f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.937297f, 0.029526f, -0.347030f, -0.013160f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.237322f, 0.673527f, -0.661455f, 0.229166f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.477907f, 0.521157f, 0.521158f, -0.477907f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.858755f, -0.091806f, -0.502290f, 0.042621f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 13  time: 0.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 13 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023644f, 0.003195f, -0.005056f);
		pTmp->poBone[4].Q = Quat(-0.003195f, 0.024007f, 0.097534f, 0.994937f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.151498f, 0.680314f, 0.621239f, 0.358167f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.547352f, -0.447667f, 0.447667f, 0.547352f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.942320f, 0.049539f, -0.330163f, -0.023903f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.256055f, 0.666562f, -0.664184f, 0.221340f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.474570f, 0.524197f, 0.524198f, -0.474570f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.867556f, -0.068883f, -0.491638f, 0.029895f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 14  time: 0.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 14 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023697f, 0.001907f, -0.004203f);
		pTmp->poBone[4].Q = Quat(-0.002106f, 0.004823f, 0.088008f, 0.996106f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.137745f, 0.681997f, 0.617550f, 0.366795f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.550391f, -0.443925f, 0.443926f, 0.550391f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.947888f, 0.072363f, -0.308074f, -0.036896f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.271973f, -0.659696f, 0.668890f, -0.208370f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.473511f, 0.525154f, 0.525155f, -0.473511f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.878790f, -0.041626f, -0.475168f, 0.014477f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 15  time: 0.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 15 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023739f, 0.000543f, -0.003283f);
		pTmp->poBone[4].Q = Quat(-0.001017f, -0.020909f, 0.076279f, 0.996867f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.120723f, 0.684945f, 0.615894f, 0.370070f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.555105f, -0.438017f, 0.438017f, 0.555105f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.953295f, 0.095471f, -0.282058f, -0.050557f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.282383f, -0.654110f, 0.675267f, -0.190826f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.475630f, 0.523236f, 0.523236f, -0.475630f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.891177f, -0.012983f, -0.453465f, -0.002082f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 16  time: 0.666667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 16 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023767f, -0.000786f, -0.002368f);
		pTmp->poBone[4].Q = Quat(-0.000260f, -0.050966f, 0.063366f, 0.996688f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.101955f, 0.688763f, 0.616459f, 0.367680f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.561093f, -0.430320f, 0.430320f, 0.561092f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.957983f, 0.116718f, -0.254170f, -0.063583f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.286199f, -0.650471f, 0.682638f, -0.170243f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.480814f, 0.518476f, 0.518477f, -0.480814f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.903369f, 0.014427f, -0.428240f, -0.018079f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 17  time: 0.708333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 17 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023776f, -0.002011f, -0.001504f);
		pTmp->poBone[4].Q = Quat(0.000000f, -0.082477f, 0.051494f, 0.995262f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.082123f, 0.692952f, 0.618560f, 0.361188f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.568110f, -0.421012f, 0.421012f, 0.568110f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.961853f, 0.134777f, -0.225918f, -0.075065f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.285385f, -0.648028f, 0.690433f, -0.148047f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.487715f, 0.511990f, 0.511991f, -0.487715f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.914208f, 0.039137f, -0.402055f, -0.032311f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 18  time: 0.750000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 18 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023751f, -0.003080f, -0.000629f);
		pTmp->poBone[4].Q = Quat(-0.000237f, -0.120071f, 0.039773f, 0.991968f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.061109f, 0.697835f, 0.622776f, 0.348486f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.574815f, -0.411810f, 0.411810f, 0.574815f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.965178f, 0.148667f, -0.197467f, -0.085656f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.276979f, -0.648211f, 0.698436f, -0.123663f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.495574f, 0.504387f, 0.504388f, -0.495573f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.924216f, 0.059736f, -0.374491f, -0.044860f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 19  time: 0.791667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 19 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.023534f, -0.004130f, 0.000356f);
		pTmp->poBone[4].Q = Quat(-0.002311f, -0.173604f, 0.018555f, 0.984638f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.041538f, 0.703761f, 0.629681f, 0.326340f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.575700f, -0.410572f, 0.410572f, 0.575700f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.966645f, 0.162223f, -0.171968f, -0.098536f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.251597f, -0.655384f, 0.705743f, -0.095383f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.504783f, -0.495170f, -0.495171f, 0.504783f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.934340f, 0.078397f, -0.342795f, -0.057912f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 20  time: 0.833333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 20 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.022906f, -0.005516f, 0.001433f);
		pTmp->poBone[4].Q = Quat(-0.008317f, -0.228717f, -0.023362f, 0.973177f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.037195f, 0.707493f, 0.635513f, 0.306911f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.566214f, -0.423558f, 0.423559f, 0.566214f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.963743f, 0.185763f, -0.153473f, -0.114616f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.215159f, -0.667758f, 0.708826f, -0.073284f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.517383f, -0.481990f, -0.481991f, 0.517383f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.944251f, 0.104083f, -0.303900f, -0.072121f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 21  time: 0.875000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 21 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.021844f, -0.007432f, 0.002542f);
		pTmp->poBone[4].Q = Quat(-0.018695f, -0.248539f, -0.072319f, 0.965737f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.053232f, 0.704719f, 0.632274f, 0.317438f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.555953f, -0.436939f, 0.436940f, 0.555953f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956718f, 0.226278f, -0.131387f, -0.127385f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.203261f, -0.671115f, 0.709393f, -0.071073f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.531333f, -0.466567f, -0.466568f, 0.531333f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.950245f, 0.146423f, -0.262509f, -0.081748f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 22  time: 0.916667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 22 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.019334f, -0.010016f, 0.003761f);
		pTmp->poBone[4].Q = Quat(-0.052190f, -0.253420f, -0.136871f, 0.956201f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.078539f, 0.695989f, 0.613998f, 0.363919f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.535067f, -0.462280f, 0.462281f, 0.535067f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956396f, 0.237992f, -0.110301f, -0.128454f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.188612f, -0.669273f, 0.717505f, -0.041065f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.546210f, -0.449059f, -0.449060f, 0.546210f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.950635f, 0.166924f, -0.251995f, -0.070195f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 23  time: 0.958333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 23 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.014923f, -0.013294f, 0.005123f);
		pTmp->poBone[4].Q = Quat(-0.120128f, -0.257896f, -0.227428f, 0.931308f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.077059f, 0.686951f, 0.582673f, 0.427378f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.518884f, -0.480374f, 0.480374f, 0.518884f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.970584f, 0.194254f, -0.071430f, -0.123002f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.166386f, -0.664804f, 0.728247f, 0.002816f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.578512f, -0.406600f, -0.406601f, 0.578512f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.971613f, 0.121990f, -0.202216f, -0.013969f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 24  time: 1.000000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 24 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010922f, -0.016627f, 0.006386f);
		pTmp->poBone[4].Q = Quat(-0.185910f, -0.259349f, -0.333522f, 0.887096f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.042952f, 0.688975f, 0.576696f, 0.436910f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.536882f, -0.460171f, 0.460172f, 0.536882f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.979821f, 0.158640f, -0.018557f, -0.120166f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.147004f, -0.659543f, 0.736060f, 0.040115f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.606831f, -0.362983f, -0.362983f, 0.606831f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.987232f, 0.085648f, -0.132805f, 0.019992f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 25  time: 1.041667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 25 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.009451f, -0.019349f, 0.007353f);
		pTmp->poBone[4].Q = Quat(-0.211696f, -0.256813f, -0.447210f, 0.830202f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.055026f, 0.695264f, 0.605858f, 0.382775f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.556573f, -0.436150f, 0.436150f, 0.556573f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.977919f, 0.182760f, 0.006012f, -0.101178f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.139987f, -0.657346f, 0.738543f, 0.053421f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.616650f, -0.346039f, -0.346040f, 0.616649f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.983387f, 0.148051f, -0.104902f, -0.005078f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 26  time: 1.083333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 26 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.009759f, -0.021502f, 0.008011f);
		pTmp->poBone[4].Q = Quat(-0.204471f, -0.241736f, -0.599364f, 0.735199f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.170647f, 0.681443f, 0.638791f, 0.313786f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.534617f, -0.462801f, 0.462802f, 0.534616f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.965336f, 0.249414f, -0.026952f, -0.072062f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.113324f, -0.670607f, 0.732560f, -0.028277f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.596734f, -0.379353f, -0.379353f, 0.596734f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.958520f, 0.246589f, -0.137612f, -0.038691f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 27  time: 1.125000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 27 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010418f, -0.023156f, 0.008359f);
		pTmp->poBone[4].Q = Quat(-0.183838f, -0.211741f, -0.744220f, 0.606223f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.343416f, 0.625251f, 0.656139f, 0.246190f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.492013f, -0.507861f, 0.507861f, 0.492013f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.949669f, 0.301093f, -0.082304f, -0.026421f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(-0.051947f, -0.689352f, 0.690840f, -0.211743f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(0.542447f, -0.453598f, -0.453598f, 0.542447f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.932988f, 0.280275f, -0.223397f, -0.032763f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 28  time: 1.166667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 28 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.024408f, 0.008588f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.405833f, 0.598137f, 0.661193f, 0.200886f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.495675f, -0.504288f, 0.504288f, 0.495675f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.946239f, 0.311026f, -0.088524f, 0.007615f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.021337f, 0.706229f, -0.635709f, 0.310901f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.498716f, 0.501281f, 0.501281f, -0.498716f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.925173f, 0.253605f, -0.281175f, -0.026089f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 29  time: 1.208333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 29 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.025461f, 0.008785f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.385687f, 0.608756f, 0.671054f, 0.174208f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.525544f, -0.473079f, 0.473079f, 0.525544f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.949912f, 0.305306f, -0.064938f, 0.015410f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.019564f, 0.731110f, -0.594907f, 0.333437f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.476375f, 0.522558f, 0.522558f, -0.476375f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.930599f, 0.207997f, -0.299327f, -0.033565f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 30  time: 1.250000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 30 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026111f, 0.008866f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.371015f, 0.616107f, 0.677886f, 0.152415f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.550376f, -0.443944f, 0.443945f, 0.550376f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.952898f, 0.299633f, -0.040149f, 0.024340f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.019115f, 0.753086f, -0.557889f, 0.348220f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.458719f, 0.538123f, 0.538124f, -0.458719f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.934461f, 0.167845f, -0.311385f, -0.040625f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 31  time: 1.291667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 31 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.364391f, 0.619618f, 0.681103f, 0.139254f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.566867f, -0.422684f, 0.422684f, 0.566867f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.954745f, 0.294994f, -0.018678f, 0.033045f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.019813f, 0.770984f, -0.528105f, 0.355381f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.447118f, 0.547801f, 0.547801f, -0.447117f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.937384f, 0.136220f, -0.316944f, -0.047980f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 32  time: 1.333333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 32 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.360965f, 0.621705f, 0.682752f, 0.130524f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.578568f, -0.406520f, 0.406521f, 0.578568f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.955759f, 0.291354f, -0.001044f, 0.040454f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.021072f, 0.783625f, -0.508032f, 0.356919f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.441314f, 0.552487f, 0.552488f, -0.441313f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.939590f, 0.115219f, -0.317607f, -0.054962f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 33  time: 1.375000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 33 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.358390f, 0.623252f, 0.683816f, 0.124535f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.586282f, -0.395314f, 0.395314f, 0.586282f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956219f, 0.288922f, 0.010823f, 0.045297f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022158f, 0.790671f, -0.497591f, 0.356021f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439394f, 0.554015f, 0.554015f, -0.439394f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.940986f, 0.104426f, -0.316299f, -0.059960f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 34  time: 1.416667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 34 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022551f, 0.792791f, -0.494689f, 0.355326f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439142f, 0.554215f, 0.554215f, -0.439142f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941451f, 0.101445f, -0.315539f, -0.061751f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 35  time: 1.458333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 35 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022561f, 0.792788f, -0.494686f, 0.355337f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439141f, 0.554216f, 0.554216f, -0.439141f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941455f, 0.101447f, -0.315528f, -0.061745f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 36  time: 1.500000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 36 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022567f, 0.792786f, -0.494683f, 0.355343f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439141f, 0.554216f, 0.554217f, -0.439140f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941458f, 0.101449f, -0.315521f, -0.061741f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 37  time: 1.541667 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 37 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022570f, 0.792786f, -0.494682f, 0.355347f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439140f, 0.554216f, 0.554217f, -0.439140f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941459f, 0.101450f, -0.315518f, -0.061739f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 38  time: 1.583333 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 38 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022570f, 0.792785f, -0.494682f, 0.355347f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439140f, 0.554216f, 0.554217f, -0.439140f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941459f, 0.101450f, -0.315518f, -0.061739f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Keyframe: 39  time: 1.625000 seconds

		pTmpX = new FrameBucket();
		pTmpX->prevBucket = pTmp;
		pTmpX->nextBucket = nullptr;
		pTmpX->KeyTime = 39 * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pTmpX->poBone = new Bone[(unsigned int)this->numBones];
		pTmp->nextBucket = pTmpX;

		pTmp = pTmpX;

		// Bone: 0 
		pTmp->poBone[0].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[0].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[0].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 1 
		pTmp->poBone[1].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[1].Q = Quat(0.000000f, 0.000000f, 0.000000f, 1.000000f);
		pTmp->poBone[1].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 2 
		pTmp->poBone[2].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[2].Q = Quat(-0.707107f, -0.000000f, 0.000000f, 0.707107f);
		pTmp->poBone[2].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 3 
		pTmp->poBone[3].T = Vec3(0.000000f, 0.000000f, 0.000000f);
		pTmp->poBone[3].Q = Quat(0.500000f, -0.500000f, 0.500000f, 0.500000f);
		pTmp->poBone[3].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 4 
		pTmp->poBone[4].T = Vec3(0.010726f, -0.026281f, 0.008876f);
		pTmp->poBone[4].Q = Quat(-0.173585f, -0.197831f, -0.790705f, 0.552735f);
		pTmp->poBone[4].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 5 
		pTmp->poBone[5].T = Vec3(0.000030f, -0.008568f, 0.000247f);
		pTmp->poBone[5].Q = Quat(-0.357458f, 0.623807f, 0.684173f, 0.122460f);
		pTmp->poBone[5].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 6 
		pTmp->poBone[6].T = Vec3(0.015902f, -0.000000f, 0.000000f);
		pTmp->poBone[6].Q = Quat(-0.588896f, -0.391410f, 0.391411f, 0.588895f);
		pTmp->poBone[6].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 7 
		pTmp->poBone[7].T = Vec3(0.014309f, 0.000000f, 0.000000f);
		pTmp->poBone[7].Q = Quat(0.956336f, 0.288091f, 0.014893f, 0.046932f);
		pTmp->poBone[7].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 8 
		pTmp->poBone[8].T = Vec3(0.000030f, 0.008568f, 0.000247f);
		pTmp->poBone[8].Q = Quat(0.022571f, 0.792785f, -0.494682f, 0.355347f);
		pTmp->poBone[8].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 9 
		pTmp->poBone[9].T = Vec3(0.015902f, 0.000000f, -0.000000f);
		pTmp->poBone[9].Q = Quat(-0.439140f, 0.554217f, 0.554217f, -0.439139f);
		pTmp->poBone[9].S = Vec3(0.999999f, 1.000000f, 1.000000f);

		// Bone: 10 
		pTmp->poBone[10].T = Vec3(0.014309f, -0.000000f, -0.000000f);
		pTmp->poBone[10].Q = Quat(0.941459f, 0.101449f, -0.315517f, -0.061739f);
		pTmp->poBone[10].S = Vec3(1.000000f, 1.000000f, 1.000000f);

		// Bone: 11 
		pTmp->poBone[11].T = Vec3(0.003649f, 0.000000f, 0.002990f);
		pTmp->poBone[11].Q = Quat(0.707107f, 0.000000f, 0.707107f, -0.000000f);
		pTmp->poBone[11].S = Vec3(1.000000f, 1.000000f, 1.000000f);
	}
}

// --- End of File ---
