//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Address.h"
#include "Address.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Address_Class, TestConfig::ALL)
{
#if Address_Class

	Trace::out("\n");

	CHECK(sizeof(Address) == 12);

	Address mA("College of Computing and Digital Media",
		       "243 South Wabash Avenue",
		       "(312) 362-8381");
	
	CHECK(strcmp(mA.poName, "College of Computing and Digital Media") == 0);
	CHECK(strcmp(mA.poAddr, "243 South Wabash Avenue") == 0);
	CHECK(strcmp(mA.poPhone, "(312) 362-8381") == 0);
	mA.Print("mA");

	Address_proto mA_proto;
	mA.Serialize(mA_proto);

	Address mB;
	mB.Deserialize(mA_proto);
	mB.Print("mB");

	size_t serialSize = mA_proto.ByteSizeLong();
	CHECK(serialSize <= 198);

	CHECK(strcmp(mA.poName, mB.poName) == 0);
	CHECK(strcmp(mA.poAddr, mB.poAddr) == 0);
	CHECK(strcmp(mA.poPhone, mB.poPhone) == 0);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Address_Class)
{
	
}

// ---  End of File ---
