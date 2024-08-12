//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Matrix_Composition.h"

void Matrix_Composition::Serialize(Matrix_Composition_proto &out) const
{
	this->v0.Serialize(*out.mutable_v0());
	this->v1.Serialize(*out.mutable_v1());
	this->v2.Serialize(*out.mutable_v2());
	this->v3.Serialize(*out.mutable_v3());
}

void Matrix_Composition::Deserialize(const Matrix_Composition_proto &in)
{
	this->v0.Deserialize(in.v0());
	this->v1.Deserialize(in.v1());
	this->v2.Deserialize(in.v2());
	this->v3.Deserialize(in.v3());
}

// --- End of File ---
