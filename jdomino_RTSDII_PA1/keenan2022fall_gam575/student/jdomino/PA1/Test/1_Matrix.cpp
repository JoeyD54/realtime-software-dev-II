//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Matrix.h"
#include "Matrix.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Matrix_Class, TestConfig::ALL)
{
#if Matrix_Class

	Trace::out("\n");

	CHECK(sizeof(Matrix) == 64);
	
	Matrix mA(11, 22, 33, 44,
			  55, 66, 77, 88,
			  99, 12, 13, 14,
			  15, 16, 17, 18);
	mA.Print("mA");

	CHECK(mA.m0 == 11);
	CHECK(mA.m1 == 22);
	CHECK(mA.m2 == 33);
	CHECK(mA.m3 == 44);
	CHECK(mA.m4 == 55);
	CHECK(mA.m5 == 66);
	CHECK(mA.m6 == 77);
	CHECK(mA.m7 == 88);
	CHECK(mA.m8 == 99);
	CHECK(mA.m9 == 12);
	CHECK(mA.m10 == 13);
	CHECK(mA.m11 == 14);
	CHECK(mA.m12 == 15);
	CHECK(mA.m13 == 16);
	CHECK(mA.m14 == 17);
	CHECK(mA.m15 == 18);

	Matrix_proto mA_proto;
	mA.Serialize(mA_proto);

	Matrix mB;
	mB.Deserialize(mA_proto);
	mB.Print("mB");
	
	size_t serialSize = mA_proto.ByteSizeLong();
	CHECK(serialSize <= 81);

	CHECK(mA.m0 == mB.m0);
	CHECK(mA.m1 == mB.m1);
	CHECK(mA.m2 == mB.m2);
	CHECK(mA.m3 == mB.m3);
	CHECK(mA.m4 == mB.m4);
	CHECK(mA.m5 == mB.m5);
	CHECK(mA.m6 == mB.m6);
	CHECK(mA.m7 == mB.m7);
	CHECK(mA.m8 == mB.m8);
	CHECK(mA.m9 == mB.m9);
	CHECK(mA.m10 == mB.m10);
	CHECK(mA.m11 == mB.m11);
	CHECK(mA.m12 == mB.m12);
	CHECK(mA.m13 == mB.m13);
	CHECK(mA.m14 == mB.m14);
	CHECK(mA.m15 == mB.m15);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Matrix_Class)
{
	
}

// ---  End of File ---
