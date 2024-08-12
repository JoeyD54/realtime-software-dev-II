//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "NullMesh.h"
#include "GraphicsObject_Null.h"

#include "GameObject.h"
#include "SimpleGameObject.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"

#include "MeshNodeMan.h"
#include "ShaderMan.h"

namespace Azul
{
	void GameObjectMan::Add(GameObject *pObj)
	{
		assert(pObj);

		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();

		// Get root node
		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();

		// insert object to root
		pGOM->poRootTree->Insert(pObj, pRootNode);
	}

	void GameObjectMan::Create()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);
		AZUL_UNUSED_VAR(pGOM);
	}

	void GameObjectMan::Destroy()
	{
		// Get singleton
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSTree *pTree = pGOM->poRootTree;
		PCSNode *pNode = nullptr;

		PCSTreeForwardIterator pForIter(pTree->GetRoot());
		pNode = pForIter.First();
		PCSNode *pTmp = nullptr;
		while (!pForIter.IsDone())
		{
			pTmp = pForIter.CurrentItem();

			pNode = pForIter.Next();
			delete pTmp;

		}
	}

	void GameObjectMan::Update(AnimTime currentTime)
	{
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode *pNode = pForwardIter.First();

		GameObject *pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject *)pNode;
			pGameObj->Update(currentTime);

			pNode = pForwardIter.Next();
		}
	}

	void GameObjectMan::Draw()
	{
		GameObjectMan *pGOM = GameObjectMan::privGetInstance();
		assert(pGOM);

		PCSNode *pRootNode = pGOM->poRootTree->GetRoot();
		assert(pRootNode);

		PCSTreeForwardIterator pForwardIter(pRootNode);
		PCSNode *pNode = pForwardIter.First();

		GameObject *pGameObj = nullptr;

		while (!pForwardIter.IsDone())
		{
			assert(pNode);
			// Update the game object
			pGameObj = (GameObject *)pNode;
			pGameObj->Draw();

			pNode = pForwardIter.Next();
		}
	}

	GameObjectMan::GameObjectMan()
	{
		// Create the root node (null object)
		NullMesh *pMesh = new NullMesh(nullptr);
		assert(pMesh);
		MeshNodeMan::Add(Mesh::Name::NULL_MESH, pMesh);

		ShaderObject* pShader = ShaderMan::Add(ShaderObject::Name::NULL_SHADER, "nullRender");
		GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pMesh, pShader);
		SimpleGameObject *pGameRoot = new SimpleGameObject(pGraphicsObject);
		//GameObject* pGameRoot = new GameObject(pGraphicsObject);
		pGameRoot->SetName("GameObject_Root");

		// Create the tree
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		// Attach the root node
		this->poRootTree->Insert(pGameRoot, this->poRootTree->GetRoot());
	}

	GameObjectMan::~GameObjectMan()
	{
		delete this->poRootTree;
	}

	GameObjectMan *GameObjectMan::privGetInstance(void)
	{
		// This is where its actually stored (BSS section)
		static GameObjectMan gom;
		return &gom;
	}

}

// --- End of File ---
