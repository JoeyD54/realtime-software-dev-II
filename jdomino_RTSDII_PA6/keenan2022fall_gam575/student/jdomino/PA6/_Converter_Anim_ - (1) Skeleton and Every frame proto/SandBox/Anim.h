//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include <vector>

#include "tiny_gltf.h"
#include "MathEngine.h"

using namespace tinygltf;
using namespace Azul;

struct Bone 
{
	Vec3  T;
	Quat  Q;
	Vec3  S;
};

struct Frame
{
	int                frameIndex;
	float              time;
	std::vector<Bone>  vectorBone;
};

struct Clip
{
	std::vector<Frame> vectorClip;
};


class ANIM
{
public:
	void CreateAnim(Model &model);

	float GetTime(Model &model, size_t accessorIndex, size_t frameIndex);
	Vec3 GetTrans(Model &model, size_t accessorIndex, size_t frameIndex);
	Quat GetQuat(Model &model, size_t accessorIndex, size_t frameIndex);

private:
	Clip clip;

};

#endif

// --- End of File ---
