//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GameObject.pb.h"
#include "Vect.h"
#include "Matrix.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class GameObject
{
public:
	GameObject();
	GameObject(const GameObject &) = delete;
	GameObject &operator = (const GameObject &) = delete;
   ~GameObject();

	GameObject(Matrix &m, Vect &externVect, float x, int i,Vect &internVect);

	// Serialization 
	void Serialize(GameObject_proto &out) const;
	void Deserialize(const GameObject_proto &in);

	void Print(const char *const pName) const;

public:
	Matrix *poMatrix;  // allocation size is known... no need to serialize size
	Vect *poVect;      // allocation size is known... no need to serialize size
	float x;
	int   i;	
	Vect vA;
};

#endif

// --- End of File ---
