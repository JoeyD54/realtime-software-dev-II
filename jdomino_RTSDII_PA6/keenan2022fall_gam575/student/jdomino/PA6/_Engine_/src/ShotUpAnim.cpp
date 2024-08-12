
#include "ShotUpAnim.h"
#include "Constants.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Mixer.h"
#include "ShotUpClip.h"


namespace Azul
{
	extern ShotUpClip* pShotUpClip;

	ShotUpAnim::ShotUpAnim()
		: pClip(nullptr),
		poBoneResult(nullptr),
		poSkeleton(nullptr),
		numBones(NUM_BONES)
	{
		this->poBoneResult = new Bone[(unsigned int)numBones]();
		assert(poBoneResult);

		this->poSkeleton = new Skeleton(this->poBoneResult, numBones, Skeleton::Position::BOTTOMRIGHT);
		assert(this->poSkeleton);

		// Get this from the AnimMan
		this->pClip = pShotUpClip;
		assert(pClip);
	}

	ShotUpAnim::~ShotUpAnim()
	{
		delete[] this->poBoneResult;
		delete   this->poSkeleton;
	}

	AnimTime ShotUpAnim::FindMaxTime()
	{
		assert(pClip);
		return this->pClip->GetTotalTime();
	}

	void ShotUpAnim::Animate(AnimTime tCurr)
	{
		this->pClip->AnimateBones(tCurr, this->poBoneResult);
	}

	void ShotUpAnim::SetLocation(Skeleton::Position newPos)
	{
		this->poSkeleton->SetLocation(newPos);
	}


	void ShotUpAnim::PoseSkeleton(GameObjectAnimSkeleton* node)
	{
		// safety
		assert(node);

		// Now get the world matrices
		GameObjectAnimSkeleton* childNode = (GameObjectAnimSkeleton*)node->GetChild();
		GameObjectAnimSkeleton* parentNode = node;

		// Normal.. valid child
		if (parentNode != nullptr && childNode != nullptr)
		{
			// starting point
			Vec3 start(0.0f, 0.0f, 0.0f);

			//  At this point, Find the two bones initial positions in world space
			//  Now get the length and directions
			Vec3 ptA;
			Vec3 ptB;
			ptA = start * (*parentNode->GetWorld());
			ptB = start * (*childNode->GetWorld());

			// direction between the anchor points of the respective bones
			Vec3 dir = ptB - ptA;

			// length of the bone 0
			float mag = dir.len();

			Mat4 S(Mat4::Scale::XYZ, 1, 1, mag);
			Quat Q(Quat::Orient::LocalToWorld, dir.getNorm(), Vec3(0.0f, 1.0f, 0.0f));
			Mat4 T(Mat4::Trans::XYZ, ptA);
			Mat4 BoneOrient = S * Q * T;
			parentNode->SetBoneOrientation(BoneOrient);
		}

		// deal with last node, when there isn't a terminal node
		if (parentNode != nullptr && childNode == nullptr)
		{
			// get the parent's parent  -> grandParent
			GameObjectAnimSkin* grandParentNode = (GameObjectAnimSkin*)parentNode->GetParent();
			assert(grandParentNode);
			Vec3 pTmp1;
			Vec3 pTmp2;
			pTmp1 = Vec3(0, 0, 0) * *grandParentNode->GetWorld();
			pTmp2 = Vec3(0, 0, 0) * *parentNode->GetWorld();
			Vec3 dir = pTmp2 - pTmp1;
			float mag = dir.len();

			Vec3 pTmp3(Vec3(0, 0, 0) * *parentNode->GetWorld());
			Vec3 pTmp4(Vec3(1, 0, 0) * *parentNode->GetWorld());
			dir = pTmp4 - pTmp3;

			Mat4 S(Mat4::Scale::XYZ, 1.0f, 1.0f, 0.1f * mag);
			Mat4 R(Mat4::Orient::LocalToWorld, dir.getNorm(), Vec3(0.0f, 1.0f, 0.0f));
			Mat4 T(Mat4::Trans::XYZ, pTmp2);

			Mat4 mTmp = S * R * T;
			parentNode->SetBoneOrientation(mTmp);
		}

	}

}

//--- End of File ----