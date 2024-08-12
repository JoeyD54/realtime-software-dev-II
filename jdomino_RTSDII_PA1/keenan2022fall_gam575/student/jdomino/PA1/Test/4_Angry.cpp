//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Angry.h"
#include "Angry.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Angry_Class, TestConfig::ALL)
{
#if Angry_Class

	Trace::out("\n");

	CHECK(sizeof(Angry) == 20);

	Angry mA(66,22,11,55,33.3f);

	CHECK(mA.arr[0] == 66);
	CHECK(mA.arr[1] == 22);
	CHECK(mA.arr[2] == 11);
	CHECK(mA.arr[3] == 55);
	CHECK(mA.value == 33.3f);

	mA.Print("mA");

	Angry_proto mA_proto;
	mA.Serialize(mA_proto);

	Angry mB;
	mB.Deserialize(mA_proto);
	mB.Print("mB");

	size_t serialSize = mA_proto.ByteSizeLong();
	CHECK(serialSize <= 12);

	CHECK(mA.arr[0] == mB.arr[0]);
	CHECK(mA.arr[1] == mB.arr[1]);
	CHECK(mA.arr[2] == mB.arr[2]);
	CHECK(mA.arr[3] == mB.arr[3]);
	CHECK(mA.value == mB.value);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Angry_Class)
{
	
}

// ---  End of File ---
