//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObject.h"

void GameObject::Serialize(GameObject_proto &out) const
{
	this->poMatrix->Serialize(*out.mutable_pomatrix());
	this->poVect->Serialize(*out.mutable_povect());

	out.set_x(this->x);
	out.set_i(this->i);

	this->vA.Serialize(*out.mutable_va());
}

void GameObject::Deserialize(const GameObject_proto &in)
{
	this->poMatrix->Deserialize(in.pomatrix());
	this->poVect->Deserialize(in.povect());

	this->x = in.x();
	this->i = in.i();

	this->vA.Deserialize(in.va());

}

// --- End of File ---
