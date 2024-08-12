//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Skeleton.h"


skeleton::skeleton()
	:nodeIndex(-1),
	nodeName(),
	parentIndex(-1),
	parentName("unknown")
{

};

void SKEL::CreateVector(Model &model)
{
	// Create a skeleton and Fill it
	this->skeletonVector.reserve(model.skins[0].joints.size());
	for(size_t i = 0; i < model.skins[0].joints.size(); i++)
	{
		skeleton tmpSkeleton;
		this->skeletonVector.push_back(tmpSkeleton);
	}

	// Walk through the nodes starting on the node they state
	size_t StartNodeIndex = (size_t)model.skins[0].joints[0];
	for(size_t i = StartNodeIndex; i < StartNodeIndex+ this->skeletonVector.size(); i++)
	{
		auto pNode = model.nodes[i];
		skeletonVector[i- StartNodeIndex].nodeIndex = (int)i;
		skeletonVector[i- StartNodeIndex].nodeName = pNode.name;
		//Trace::out("%d: %s \n", i, pNode.name.c_str());
		for(size_t j = 0; j < pNode.children.size(); j++)
		{
			skeletonVector[(size_t)pNode.children[j]- StartNodeIndex].nodeIndex = pNode.children[j];
			skeletonVector[(size_t)pNode.children[j]- StartNodeIndex].nodeName = model.nodes[(size_t)pNode.children[j]].name;
			skeletonVector[(size_t)pNode.children[j]- StartNodeIndex].parentIndex = (int)i;
			skeletonVector[(size_t)pNode.children[j]- StartNodeIndex].parentName = pNode.name;
			//Trace::out("\t child: (%d) %s \n", pNode.children[j], model.nodes[(size_t)pNode.children[j]].name.c_str());
		}
	}

	Trace::out("\n");
	Trace::out("\n");

	// print skeletonVector
	for(size_t i = 0; i < skeletonVector.size(); i++)
	{
		Trace::out("%2d:  node(%2d): %11s  parent(%2d): %11s\n",
			i,
			skeletonVector[i].nodeIndex,
			skeletonVector[i].nodeName.c_str(),
			skeletonVector[i].parentIndex,
			skeletonVector[i].parentName.c_str());
	}

	Trace::out("\n");
	Trace::out("\n");

	// Fill skeletonTable
	skeletonTable.reserve(skeletonVector.size());
	for(size_t i = 0; i < skeletonVector.size(); i++)
	{
		skeleton_table table;

		table.nodeIndex = skeletonVector[i].nodeIndex;
		table.parentIndex = skeletonVector[i].parentIndex;

		// Copy the string
		memset(table.nodeName, 0, skeleton_table::SKELETON_NAME_SIZE);
		strncpy_s(table.nodeName, 
			skeleton_table::SKELETON_NAME_SIZE, 
			skeletonVector[i].nodeName.c_str(), 
			skeleton_table::SKELETON_NAME_SIZE-1);

		skeletonTable.push_back(table);
	}

	// print skeletonTable
	for(size_t i = 0; i < skeletonTable.size(); i++)
	{
		Trace::out("%2d:  n:%2d  p%2d  n:%s\n",
			i,
			skeletonTable[i].nodeIndex,
			skeletonTable[i].parentIndex,
			skeletonTable[i].nodeName);
	}


	Trace::out("\n");
	Trace::out("\n");

	// print skeletonTable
	for(size_t i = 0; i < skeletonTable.size(); i++)
	{
		Trace::out("{%2d, %2d, \"%s\" },\n",
			skeletonTable[i].nodeIndex,
			skeletonTable[i].parentIndex,
			skeletonTable[i].nodeName);
	}
}


// --- End of File ---
