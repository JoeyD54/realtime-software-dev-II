//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Vect::Vect(float _x, float _y, float _z, float _w)
	:x(_x),
	y(_y),
	z(_z),
	w(_w)
{

}

void Vect::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("    %f %f %f %f\n", this->x, this->y, this->z, this->w);
}

// --- End of File ---
