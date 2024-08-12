//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PCSTreeForwardIterator.h"

#include "GraphicsObject_Null.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_FlatTexture.h"
#include "GameObjectMan.h"
#include "GameObjectBasic.h"
#include "GameObjectRigid.h"
#include "GameObjectAnimSkeleton.h"
#include "GameObjectAnimSkin.h"
#include "ShaderMan.h"
#include "Skeleton.h"
#include "MeshNodeMan.h"


namespace Azul
{
	// Move to proto file
	Skeleton::Data skel[]
	{
		{ 4, -1, "Bone" },
		{ 5,  4, "Bone_L" },
		{ 6,  5, "Bone_L_001" },
		{ 7,  6, "Bone_L_002" },
		{ 8,  4, "Bone_R" },
		{ 9,  8, "Bone_R_001" },
		{10,  9, "Bone_R_002" },
		{11,  4, "Bone_001" }
	};

	Skeleton::Skeleton(Bone *pBone, int _numBones)
	: pFirstBone(nullptr),
		numBones(_numBones)
	{
		this->privSetAnimationHierarchy(pBone);
		assert(pFirstBone);
	}

	Skeleton::Skeleton(Bone* pBone, int numBones, Skeleton::Position pos)
		: pFirstBone(nullptr),
		numBones(numBones),
		myPos(pos)
	{
		this->privSetAnimationHierarchy(pBone);	
		assert(pFirstBone);
	}

	Skeleton::~Skeleton()
	{

	}

	void Skeleton::SetLocation(Position pos)
	{
		if (pos == Position::CENTER)
		{
			pPivot->SetScale(80, 80, 80);
			pPivot->SetTrans(-3, 0, 0);
		}
		else if (pos == Position::TOPLEFT)
		{
			pPivot->SetScale(50, 50, 50);
			pPivot->SetTrans(-1, 0, -3);
		}
		else if (pos == Position::TOPRIGHT)
		{
			pPivot->SetScale(50, 50, 50);
			pPivot->SetTrans(-1, 0, 3);
		}
		else if (pos == Position::BOTTOMLEFT)
		{
			pPivot->SetScale(50, 50, 50);
			pPivot->SetTrans(-4, 0, -3);
		}
		else  //bottom right
		{
			pPivot->SetScale(50, 50, 50);
			pPivot->SetTrans(-4, 0, 3);
		}
	}

	GameObjectAnim *Skeleton::GetFirstBone()
	{
		assert(pFirstBone);
		return this->pFirstBone;
	}

	GameObjectAnim *Skeleton::privFindBoneByIndex(int index)
	{
		GameObjectAnim *pFound = nullptr;

		GameObjectAnim *pObj = this->GetFirstBone();

		// TODO - add test bed for an interator of a tree with only one node
		if(pObj->index == index)
		{
			pFound = pObj;
		}
		else
		{
			PCSTreeForwardIterator pIter(pObj);
			PCSNode *pNode = pIter.First();
			GameObjectAnim *pGameObj = nullptr;

			// walks the anim node does the pose for everything that
			while(pNode != nullptr)
			{
				assert(pNode);
				// Update the game object
				pGameObj = (GameObjectAnim *)pNode;
				if(pGameObj->index == index)
				{
					pFound = pGameObj;
					break;
				}
				pNode = pIter.Next();
			}
		}

		return pFound;
	}

	void Skeleton::privSetAnimationHierarchy(Bone *pBoneResult)
	{
#if 1
		// Load Shader 
		ShaderObject *pShaderObject_texture = ShaderMan::Find(ShaderObject::Name::TEXTURE_SIMPLE);
		assert(pShaderObject_texture);

		// Mesh - Rigid models for our animation (skin weight = 1)
		Mesh *MeshArray[8];

		MeshArray[0] = MeshNodeMan::Find(Mesh::Name::Bone);
		MeshArray[1] = MeshNodeMan::Find(Mesh::Name::Bone_L);
		MeshArray[2] = MeshNodeMan::Find(Mesh::Name::Bone_L_001);
		MeshArray[3] = MeshNodeMan::Find(Mesh::Name::Bone_L_002);
		MeshArray[4] = MeshNodeMan::Find(Mesh::Name::Bone_R);
		MeshArray[5] = MeshNodeMan::Find(Mesh::Name::Bone_R_001);
		MeshArray[6] = MeshNodeMan::Find(Mesh::Name::Bone_R_002);
		MeshArray[7] = MeshNodeMan::Find(Mesh::Name::Bone_001);

		// GraphicsObject for a specific instance
		GraphicsObject *pGraphicsObj;

		//---------------------------------------
		// ChickenBot
		//---------------------------------------

		// Add A Dummy pivot object
			Mesh *pMeshNull = MeshNodeMan::Find(Mesh::Name::NULL_MESH);
			assert(pMeshNull);

			ShaderObject *pShaderNull = ShaderMan::Find(ShaderObject::Name::NULL_SHADER);
			assert(pShaderNull);

			pGraphicsObj = new GraphicsObject_Null(pMeshNull, pShaderNull);
			pPivot = new GameObjectBasic(pGraphicsObj);
			pPivot->SetName("Pivot");
			pPivot->DrawDisable();
			pPivot->delta_x = 0.0f;
			this->SetLocation(myPos);

			GameObjectMan::Add(pPivot, GameObjectMan::GetRoot());

		// Animation
		GameObjectAnim *pGameObj;

		// Root animation is treated differently
		for(int i = 0; i < 1; i++)
		{
			pGraphicsObj = new GraphicsObject_FlatTexture(MeshArray[i], pShaderObject_texture, Texture::Name::CHICKEN_BOT);
			pGameObj = new GameObjectAnimSkin(pGraphicsObj, pBoneResult);
			pGameObj->SetIndex(skel[i].index);
			pGameObj->SetName(skel[i].name);

			GameObjectMan::Add(pGameObj, pPivot);
			this->pFirstBone = pGameObj;
		}

		for(int i = 1; i < this->numBones-4; i++)
		{
			pGraphicsObj = new GraphicsObject_FlatTexture(MeshArray[i], pShaderObject_texture, Texture::Name::CHICKEN_BOT);
			pGameObj = new GameObjectAnimSkin(pGraphicsObj, pBoneResult);
			pGameObj->SetIndex(skel[i].index);
			pGameObj->SetName(skel[i].name);

			GameObjectAnim *pParent = this->privFindBoneByIndex(skel[i].parentIndex);
			assert(pParent);
			GameObjectMan::Add(pGameObj, pParent);
		}

#else

		// Load the mesh
		Mesh *pPyramidMesh = MeshNodeMan::Find(Mesh::Name::PYRAMID);
		assert(pPyramidMesh);

		// Load Shader 
		ShaderObject *pShaderObject_textureLight = ShaderMan::Find(ShaderObject::Name::TEXTURE_POINT_LIGHT);
		assert(pShaderObject_textureLight);

		// GraphicsObject for a specific instance
		GraphicsObject *pGraphicsObj;

		// Create GameObject
		Vec4 color(1.20f,1.20f, 1.20f, 1.0f);
		Vec3 pos(1, 1, 1);

		//---------------------------------------
		// ChickenBot
		//---------------------------------------
		
		// Add A Dummy pivot object
			Mesh *pMeshNull = MeshNodeMan::Find(Mesh::Name::NULL_MESH);
			assert(pMeshNull);

			ShaderObject *pShaderNull = ShaderMan::Find(ShaderObject::Name::NULL_SHADER);
			assert(pShaderNull);

			pGraphicsObj = new GraphicsObject_Null(pMeshNull, pShaderNull);
			GameObjectBasic *pPivot = new GameObjectBasic(pGraphicsObj);
			pPivot->SetName("Pivot");
			pPivot->DrawDisable();
			pPivot->delta_x = 0.0f;
			pPivot->SetScale(100, 100, 100);
			pPivot->SetTrans(-3, 0, 0);

			GameObjectMan::Add(pPivot, GameObjectMan::GetRoot());

		// Animation objects:
		GameObjectAnim *pGameObj;

		// Root animation is treated differently
		for(int i = 0; i < 1; i++)
		{
			pGraphicsObj = new GraphicsObject_TextureLight(pPyramidMesh, pShaderObject_textureLight, Texture::Name::DUCKWEED, color, pos);
			pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
			pGameObj->SetIndex(skel[i].index);
			pGameObj->SetName(skel[i].name);

			GameObjectMan::Add(pGameObj, pPivot);
			this->pFirstBone = pGameObj;
		}

		for(int i = 1; i < this->numBones - 4; i++)
		{
			pGraphicsObj = new GraphicsObject_TextureLight(pPyramidMesh, pShaderObject_textureLight, Texture::Name::DUCKWEED, color, pos);
			pGameObj = new GameObjectAnimSkeleton(pGraphicsObj, pBoneResult);
			pGameObj->SetIndex(skel[i].index);
			pGameObj->SetName(skel[i].name);

			GameObjectAnim *pParent = this->privFindBoneByIndex(skel[i].parentIndex);

			GameObjectMan::Add(pGameObj, pParent);
		}

		//PCSTree *pTree = GameObjectMan::GetPCSTree();
		//pTree->Print();

#endif

	}


}

// --- End of File ---
