//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Matrix_Composition.h"
#include "Matrix_Composition.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Matrix_Composition_Class, TestConfig::ALL)
{
#if Matrix_Composition_Class

	Trace::out("\n");

	CHECK(sizeof(Matrix_Composition) == 64);

	Vect vA(11, 22, 33, 44);
	Vect vB(55, 66, 77, 88);
	Vect vC(99, 12, 13, 14);
	Vect vD(15, 16, 17, 18);

	CHECK(vA.x == 11);
	CHECK(vA.y == 22);
	CHECK(vA.z == 33);
	CHECK(vA.w == 44);

	CHECK(vB.x == 55);
	CHECK(vB.y == 66);
	CHECK(vB.z == 77);
	CHECK(vB.w == 88);

	CHECK(vC.x == 99);
	CHECK(vC.y == 12);
	CHECK(vC.z == 13);
	CHECK(vC.w == 14);

	CHECK(vD.x == 15);
	CHECK(vD.y == 16);
	CHECK(vD.z == 17);
	CHECK(vD.w == 18);

	Matrix_Composition mA(vA,vB,vC,vD);
	mA.Print("mA");

	CHECK(mA.v0.x == 11);
	CHECK(mA.v0.y == 22);
	CHECK(mA.v0.z == 33);
	CHECK(mA.v0.w == 44);
	CHECK(mA.v1.x == 55);
	CHECK(mA.v1.y == 66);
	CHECK(mA.v1.z == 77);
	CHECK(mA.v1.w == 88);
	CHECK(mA.v2.x == 99);
	CHECK(mA.v2.y == 12);
	CHECK(mA.v2.z == 13);
	CHECK(mA.v2.w == 14);
	CHECK(mA.v3.x == 15);
	CHECK(mA.v3.y == 16);
	CHECK(mA.v3.z == 17);
	CHECK(mA.v3.w == 18);

	Matrix_Composition_proto mA_proto;
	mA.Serialize(mA_proto);

	Matrix_Composition mB;
	mB.Deserialize(mA_proto);
	mB.Print("mB");

	size_t serialSize = mA_proto.ByteSizeLong();
	CHECK(serialSize <= 88);

	CHECK(mA.v0.x == mB.v0.x);
	CHECK(mA.v0.y == mB.v0.y);
	CHECK(mA.v0.z == mB.v0.z);
	CHECK(mA.v0.w == mB.v0.w);
	CHECK(mA.v1.x == mB.v1.x);
	CHECK(mA.v1.y == mB.v1.y);
	CHECK(mA.v1.z == mB.v1.z);
	CHECK(mA.v1.w == mB.v1.w);
	CHECK(mA.v2.x == mB.v2.x);
	CHECK(mA.v2.y == mB.v2.y);
	CHECK(mA.v2.z == mB.v2.z);
	CHECK(mA.v2.w == mB.v2.w);
	CHECK(mA.v3.x == mB.v3.x);
	CHECK(mA.v3.y == mB.v3.y);
	CHECK(mA.v3.z == mB.v3.z);
	CHECK(mA.v3.w == mB.v3.w);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Matrix_Composition_Class)
{
	
}

// ---  End of File ---
