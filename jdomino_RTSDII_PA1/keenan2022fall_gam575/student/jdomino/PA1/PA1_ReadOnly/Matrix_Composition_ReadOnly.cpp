//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Matrix_Composition.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Matrix_Composition::Matrix_Composition(Vect &_v0, Vect &_v1, Vect &_v2, Vect &_v3)
	: v0(_v0), v1(_v1), v2(_v2), v3(_v3)
{

}

void Matrix_Composition::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("  v0: %f %f %f %f\n", this->v0.x, this->v0.y, this->v0.z, this->v0.w);
	Trace::out("  v1: %f %f %f %f\n", this->v1.x, this->v1.y, this->v1.z, this->v1.w);
	Trace::out("  v2: %f %f %f %f\n", this->v2.x, this->v2.y, this->v2.z, this->v2.w);
	Trace::out("  v3: %f %f %f %f\n", this->v3.x, this->v3.y, this->v3.z, this->v3.w);
}

// --- End of File ---
