//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Vect.h"
#include "Vect.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Vect_Class, TestConfig::ALL)
{
#if Vect_Class

	CHECK(sizeof(Vect) == 16);

	Vect vA(11.1f, 22.2f, 33.3f, 44.4f);
	vA.Print("vA");

	CHECK(vA.x == 11.1f);
	CHECK(vA.y == 22.2f);
	CHECK(vA.z == 33.3f);
	CHECK(vA.w == 44.4f);

	Vect_proto vA_proto;
	vA.Serialize(vA_proto);

	size_t serialSize = vA_proto.ByteSizeLong();
	CHECK(serialSize <= 20);

	Vect vB;
	vB.Deserialize(vA_proto);
	vB.Print("vB");

	Trace::out("\n");

	CHECK(vA.x == vB.x);
	CHECK(vA.y == vB.y);
	CHECK(vA.z == vB.z);
	CHECK(vA.w == vB.w);

#endif
} TEST_END

TEST_TEARDOWN(Vect_Class)
{
	
}

// ---  End of File ---
