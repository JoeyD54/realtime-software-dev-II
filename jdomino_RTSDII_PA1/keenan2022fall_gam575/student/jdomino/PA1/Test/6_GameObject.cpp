//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "GameObject.h"
#include "GameObject.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(GameObject_Class, TestConfig::ALL)
{
#if GameObject_Class

	Trace::out("\n");

	CHECK(sizeof(GameObject) == 32);

	Matrix mA(91, 92, 93, 94, 81, 82, 83, 84, 71, 72, 73, 74, 61, 62, 63, 64);
	Vect   vA(4, 5, 6, 7);
	Vect   vB(31, 32, 33, 34);

	CHECK(mA.m0 == 91);
	CHECK(mA.m1 == 92);
	CHECK(mA.m2 == 93);
	CHECK(mA.m3 == 94);
	CHECK(mA.m4 == 81);
	CHECK(mA.m5 == 82);
	CHECK(mA.m6 == 83);
	CHECK(mA.m7 == 84);
	CHECK(mA.m8 == 71);
	CHECK(mA.m9 == 72);
	CHECK(mA.m10 == 73);
	CHECK(mA.m11 == 74);
	CHECK(mA.m12 == 61);
	CHECK(mA.m13 == 62);
	CHECK(mA.m14 == 63);
	CHECK(mA.m15 == 64);

	CHECK(vA.x == 4);
	CHECK(vA.y == 5);
	CHECK(vA.z == 6);
	CHECK(vA.w == 7);

	CHECK(vB.x == 31);
	CHECK(vB.y == 32);
	CHECK(vB.z == 33);
	CHECK(vB.w == 34);

	GameObject gA(mA, vA, 17.1f, 34, vB);
	gA.Print("gA");

	CHECK(gA.poMatrix->m0 == 91);
	CHECK(gA.poMatrix->m1 == 92);
	CHECK(gA.poMatrix->m2 == 93);
	CHECK(gA.poMatrix->m3 == 94);
	CHECK(gA.poMatrix->m4 == 81);
	CHECK(gA.poMatrix->m5 == 82);
	CHECK(gA.poMatrix->m6 == 83);
	CHECK(gA.poMatrix->m7 == 84);
	CHECK(gA.poMatrix->m8 == 71);
	CHECK(gA.poMatrix->m9 == 72);
	CHECK(gA.poMatrix->m10 == 73);
	CHECK(gA.poMatrix->m11 == 74);
	CHECK(gA.poMatrix->m12 == 61);
	CHECK(gA.poMatrix->m13 == 62);
	CHECK(gA.poMatrix->m14 == 63);
	CHECK(gA.poMatrix->m15 == 64);

	CHECK(gA.poVect->x == 4);
	CHECK(gA.poVect->y == 5);
	CHECK(gA.poVect->z == 6);
	CHECK(gA.poVect->w == 7);

	CHECK(gA.x == 17.1f);
	CHECK(gA.i == 34);

	CHECK(gA.vA.x == 31);
	CHECK(gA.vA.y == 32);
	CHECK(gA.vA.z == 33);

	GameObject_proto gA_proto;
	gA.Serialize(gA_proto);

	GameObject gB;
	gB.Deserialize(gA_proto);
	gB.Print("mB");

	size_t serialSize = gA_proto.ByteSizeLong();
	CHECK(serialSize <= 134);

	CHECK(gB.poMatrix != nullptr);

	CHECK(gA.poMatrix->m0 == gB.poMatrix->m0);
	CHECK(gA.poMatrix->m1 == gB.poMatrix->m1);
	CHECK(gA.poMatrix->m2 == gB.poMatrix->m2);
	CHECK(gA.poMatrix->m3 == gB.poMatrix->m3);
	CHECK(gA.poMatrix->m4 == gB.poMatrix->m4);
	CHECK(gA.poMatrix->m5 == gB.poMatrix->m5);
	CHECK(gA.poMatrix->m6 == gB.poMatrix->m6);
	CHECK(gA.poMatrix->m7 == gB.poMatrix->m7);
	CHECK(gA.poMatrix->m8 == gB.poMatrix->m8);
	CHECK(gA.poMatrix->m9 == gB.poMatrix->m9);
	CHECK(gA.poMatrix->m10 == gB.poMatrix->m10);
	CHECK(gA.poMatrix->m11 == gB.poMatrix->m11);
	CHECK(gA.poMatrix->m12 == gB.poMatrix->m12);
	CHECK(gA.poMatrix->m13 == gB.poMatrix->m13);
	CHECK(gA.poMatrix->m14 == gB.poMatrix->m14);
	CHECK(gA.poMatrix->m15 == gB.poMatrix->m15);

	CHECK(gA.poVect->x == gB.poVect->x);
	CHECK(gA.poVect->y == gB.poVect->y);
	CHECK(gA.poVect->z == gB.poVect->z);
	CHECK(gA.poVect->w == gB.poVect->w);

	CHECK(gA.x == gB.x);
	CHECK(gA.i == gB.i);

	CHECK(gA.vA.x == gB.vA.x);
	CHECK(gA.vA.y == gB.vA.y);
	CHECK(gA.vA.z == gB.vA.z);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(GameObject_Class)
{

}

// ---  End of File ---
