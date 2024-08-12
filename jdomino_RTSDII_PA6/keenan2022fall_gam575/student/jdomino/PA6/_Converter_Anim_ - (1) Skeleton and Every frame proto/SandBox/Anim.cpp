//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Anim.h"
#include "GLTF.h"

using namespace tinygltf;
using namespace Azul;


void ANIM::CreateAnim(Model &model)
{
	// Create a default frame

	// YES its too big... reduce at the end
	size_t numBones = model.nodes.size();

	// Default Bone
	Bone defaultBone;
	defaultBone.T = Vec3(0.0f, 0.0f, 0.0f);
	defaultBone.Q = Quat(0.0f, 0.0f, 0.0f, 1.0f);
	defaultBone.S = Vec3(1.0f, 1.0f, 1.0f);

	// Default Frame
	Frame defaultFrame;
	defaultFrame.frameIndex = -1;
	defaultFrame.time = -1.0f;
	defaultFrame.vectorBone.reserve(numBones);
	for(size_t i = 0; i < numBones; i++)
	{
		defaultFrame.vectorBone.push_back(defaultBone);
	}

	// Correct for Stationary data:
	for(size_t i = 0; i < model.nodes.size(); i++)
	{
		// MAGIC---> use reference
		auto Node = model.nodes[i];
		defaultFrame.vectorBone[i].T = Vec3((float)Node.translation[0],(float)Node.translation[1],(float)Node.translation[2]);
		defaultFrame.vectorBone[i].Q = Quat((float)Node.rotation[0], (float)Node.rotation[1], (float)Node.rotation[2], (float)Node.rotation[3]);
		defaultFrame.vectorBone[i].S = Vec3((float)Node.scale[0], (float)Node.scale[1], (float)Node.scale[2]);
	}

	// At this point we now have a default frame filled with stationary data
	// Next let's create animation clip

	// number of frames of data?
	// it should be the same size as time elements
	size_t numAnimFrames = model.accessors[0].count;

	// hard check for walk anim... I looked at data its 40, will change with different animations
	//assert(numAnimFrames == 40);

	this->clip.vectorClip.reserve(numAnimFrames);
	// initially copy the default frame with stationary data
	for(size_t i = 0; i < numAnimFrames; i++)
	{
		this->clip.vectorClip.push_back(defaultFrame);
	}

	// At this point we have the whole animation loaded with stationary
	// replace with the animated fields
	Trace::out("\n");

	for(size_t i = 0; i < numAnimFrames; i++)
	{
		// MAGIC---> use reference
		auto &tmpClip = this->clip.vectorClip[i];

		tmpClip.frameIndex = (int)i;
		tmpClip.time = this->GetTime(model, 0, i);
		
		// overwrite the animation data into bone vector
		// iterate across the channels
		for(size_t k = 0; k < model.animations[0].channels.size(); k++)
		{
			size_t targetIndex = (size_t)model.animations[0].channels[k].target_node;
			if(model.animations[0].channels[k].target_path == "translation")
			{
			//	Trace::out("channel:%d n:%d trans\n", k,targetIndex);
				// Remember 0 is the time...so the channels are +1 index
				size_t accessorIndex = k + 1;  
				Vec3 vTmp = this->GetTrans(model, accessorIndex, i);
				tmpClip.vectorBone[targetIndex].T = vTmp;

			}
			else if(model.animations[0].channels[k].target_path == "rotation")
			{
			//	Trace::out("channel:%d n:%d rotation\n", k, targetIndex);
				// Remember 0 is the time...so the channels are +1 index
				size_t accessorIndex = k + 1;
				Quat qTmp = this->GetQuat(model, accessorIndex, i);
				tmpClip.vectorBone[targetIndex].Q = qTmp;
			}
			else
			{
				assert(false);
			}
		}

		//Trace::out("%d t:%f \n", tmpClip.frameIndex, tmpClip.time);
	}

	Trace::out("\n\n");

	// Look at the first Frame and compare with Code:
	for(size_t i = 0; i < this->clip.vectorClip.size(); i++)
	{
		auto tmpClip = clip.vectorClip[i];
		Trace::out("// Keyframe: %d  time: %f seconds\n", tmpClip.frameIndex,tmpClip.time);
		Trace::out("\n");

		Trace::out("pTmpX = new FrameBucket();\n");
		Trace::out("pTmpX->prevBucket = pTmp;\n");
		Trace::out("pTmpX->nextBucket = nullptr;\n");
		Trace::out("pTmpX->KeyTime = %d * AnimTime(AnimTime::Duration::FILM_24_FRAME); \n", i);
		Trace::out("pTmpX->poBone = new Bone[(unsigned int)this->numBones]; \n");
		Trace::out("pTmp->nextBucket = pTmpX; \n");
		Trace::out("\n");
		Trace::out("pTmp = pTmpX;\n");
		Trace::out("\n");

		for(size_t k = 0; k < tmpClip.vectorBone.size(); k++)
		{	
			// todo clean up this hack
			if(k == 12)
			{
				break;
			}

			Bone tmpBone = tmpClip.vectorBone[k];
			Trace::out("// Bone: %d \n", k);
			Trace::out("pTmp->poBone[%d].T = Vec3( %ff, %ff, %ff ); \n", k, tmpBone.T[x], tmpBone.T[y], tmpBone.T[z]);
			Trace::out("pTmp->poBone[%d].Q = Quat( %ff, %ff, %ff, %ff ); \n", k, tmpBone.Q[x], tmpBone.Q[y], tmpBone.Q[z],tmpBone.Q[w]);
			Trace::out("pTmp->poBone[%d].S = Vec3( %ff, %ff, %ff ); \n", k, tmpBone.S[x], tmpBone.S[y], tmpBone.S[z]);
			Trace::out("\n");

		}		
	}



}

float ANIM::GetTime(Model &model, size_t accessorIndex, size_t frameIndex)
{
	//Trace::out("Time: \n");
	unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
	auto TimeAccessor = model.accessors[accessorIndex];
	auto TimeBuffView = model.bufferViews[(size_t)TimeAccessor.bufferView];

	pBuff = pBuff + TimeBuffView.byteOffset;

	assert(TimeAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
	assert(TimeAccessor.type == TINYGLTF_TYPE_SCALAR);

	float *pFloatData = (float *)pBuff;

	float val = pFloatData[frameIndex];

	// sanity check
	size_t len = ((size_t)&pFloatData[frameIndex] - (size_t)pBuff);
	assert(len <= TimeBuffView.byteLength);

	return val;
}

Vec3 ANIM::GetTrans(Model &model, size_t accessorIndex, size_t frameIndex)
{
	//Trace::out("Trans 4: \n");
	unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
	auto TransAccessor = model.accessors[accessorIndex];
	auto TransBuffView = model.bufferViews[(size_t)TransAccessor.bufferView];

	pBuff = pBuff + TransBuffView.byteOffset;
	assert(TransAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
	assert(TransAccessor.type == TINYGLTF_TYPE_VEC3);
	fVect3 *pVect3 = (fVect3 *)pBuff;

	Vec3 vOut(pVect3[frameIndex].x, pVect3[frameIndex].y, pVect3[frameIndex].z);

	// sanity check
	size_t len = ((size_t)&pVect3[frameIndex] - (size_t)pBuff);
	assert(len <= TransBuffView.byteLength);

	return vOut;
}

Quat ANIM::GetQuat(Model &model, size_t accessorIndex, size_t frameIndex)
{
	//	Trace::out("Quat 4: \n");
	unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
	auto QuatAAccessor =model.accessors[accessorIndex];
	auto QuatABuffView =model.bufferViews[(size_t)QuatAAccessor.bufferView];

	pBuff = pBuff + QuatABuffView.byteOffset;
	assert(QuatAAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
	assert(QuatAAccessor.type == TINYGLTF_TYPE_VEC4);
	fVect4 *pVect4 = (fVect4 *)pBuff;

	Quat qOut(pVect4[frameIndex].x, pVect4[frameIndex].y, pVect4[frameIndex].z, pVect4[frameIndex].w);

	// sanity check
	size_t len = ((size_t)&pVect4[frameIndex] - (size_t)pBuff);
	assert(len <= QuatABuffView.byteLength);

	return qOut;
}

// --- End of File ---
