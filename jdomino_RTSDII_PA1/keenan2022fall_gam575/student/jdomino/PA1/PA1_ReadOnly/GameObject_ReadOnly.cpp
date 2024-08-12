//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObject.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

GameObject::GameObject()
	: poMatrix(new Matrix()),
	poVect(new Vect()),
	x(0),
	i(0),
	vA()
{
	assert(this->poMatrix);
	assert(this->poVect);
}

GameObject::GameObject(Matrix &m, Vect &externVect, float _x, int _i, Vect &internVect)
	: poMatrix(new Matrix(m)),
	poVect(new Vect(externVect)),
	x(_x),
	i(_i),
	vA(internVect)
{
	assert(this->poMatrix);
	assert(this->poVect);
}

GameObject::~GameObject()
{
	delete this->poMatrix;
	delete this->poVect;
}

void GameObject::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	this->poMatrix->Print("   poMatrix");
	this->poVect->Print("   poVect");
	Trace::out("   x: \n    %f \n", this->x);
	Trace::out("   i: \n    %d \n", this->i);
	this->vA.Print("   vA");
}

// --- End of File ---
