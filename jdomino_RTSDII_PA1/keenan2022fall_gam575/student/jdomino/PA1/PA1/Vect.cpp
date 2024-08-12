//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect.h"

void Vect::Serialize(Vect_proto &out) const
{
	out.set_x(this->x);
	out.set_y(this->y);
	out.set_z(this->z);
	out.set_w(this->w);
}

void Vect::Deserialize(const Vect_proto &in)
{
	this->x = in.x();
	this->y = in.y();
	this->z = in.z();
	this->w = in.w();
}

// --- End of File ---
