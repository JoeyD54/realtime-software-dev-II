//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Matrix.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

Matrix::Matrix(float _m0, float _m1, float _m2, float _m3,
	float _m4, float _m5, float _m6, float _m7,
	float _m8, float _m9, float _m10, float _m11,
	float _m12, float _m13, float _m14, float _m15)
	: m0(_m0), m1(_m1), m2(_m2), m3(_m3),
	m4(_m4), m5(_m5), m6(_m6), m7(_m7),
	m8(_m8), m9(_m9), m10(_m10), m11(_m11),
	m12(_m12), m13(_m13), m14(_m14), m15(_m15)
{

}

void Matrix::Print(const char *const pName) const
{
	Trace::out("%s: \n", pName);
	Trace::out("    %f %f %f %f\n", this->m0, this->m1, this->m2, this->m3);
	Trace::out("    %f %f %f %f\n", this->m4, this->m5, this->m6, this->m7);
	Trace::out("    %f %f %f %f\n", this->m8, this->m9, this->m10, this->m11);
	Trace::out("    %f %f %f %f\n", this->m12, this->m13, this->m14, this->m15);
}

// --- End of File ---
