//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Matrix.h"

void Matrix::Serialize(Matrix_proto &out) const
{
	out.set_m0(this->m0);
	out.set_m1(this->m1);
	out.set_m2(this->m2);
	out.set_m3(this->m3);
	out.set_m4(this->m4);
	out.set_m5(this->m5);
	out.set_m6(this->m6);
	out.set_m7(this->m7);
	out.set_m8(this->m8);
	out.set_m9(this->m9);
	out.set_m10(this->m10);
	out.set_m11(this->m11);
	out.set_m12(this->m12);
	out.set_m13(this->m13);
	out.set_m14(this->m14);
	out.set_m15(this->m15);
}

void Matrix::Deserialize(const Matrix_proto &in)
{
	this->m0 = in.m0();
	this->m1 = in.m1();
	this->m2 = in.m2();
	this->m3 = in.m3();
	this->m4 = in.m4();
	this->m5 = in.m5();
	this->m6 = in.m6();
	this->m7 = in.m7();
	this->m8 = in.m8();
	this->m9 = in.m9();
	this->m10 = in.m10();
	this->m11 = in.m11();
	this->m12 = in.m12();
	this->m13 = in.m13();
	this->m14 = in.m14();
	this->m15 = in.m15();
}

// --- End of File ---
