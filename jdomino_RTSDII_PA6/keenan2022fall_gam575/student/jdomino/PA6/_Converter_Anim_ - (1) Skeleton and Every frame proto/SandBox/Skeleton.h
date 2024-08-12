//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include <vector>

#include "tiny_gltf.h"
#include "MathEngine.h"

using namespace tinygltf;
using namespace Azul;

struct skeleton
{
	skeleton();
	skeleton(const skeleton &) = default;
	skeleton &operator = (const skeleton &) = default;
	~skeleton() = default;

	int          nodeIndex;
	std::string  nodeName;
	int          parentIndex;
	std::string  parentName;
};

struct skeleton_table
{
	static const unsigned int SKELETON_NAME_SIZE = 64;

	skeleton_table() = default;
	skeleton_table(const skeleton_table &) = default;
	skeleton_table &operator = (const skeleton_table &) = default;
   ~skeleton_table() = default;

	int   nodeIndex;
	int   parentIndex;
	char  nodeName[SKELETON_NAME_SIZE];
};

class SKEL
{
public:
	void CreateVector(Model &model);

private:
	std::vector<skeleton>      skeletonVector;
	std::vector<skeleton_table> skeletonTable;

};

#endif

// --- End of File ---
