//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Material.h"
#include "Material.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Material_Class, TestConfig::ALL)
{
#if Material_Class

	Trace::out("\n");

	CHECK(sizeof(Material) == 16);

	Material mA(Material::Color::Yellow, Material::Color::Blue, Material::Color::White, 55);

	CHECK(mA.a == Material::Color::Yellow);
	CHECK(mA.b == Material::Color::Blue);
	CHECK(mA.c == Material::Color::White);
	CHECK(mA.x == 55);

	mA.Print("mA");

	Material_proto mA_proto;
	mA.Serialize(mA_proto);

	Material mB;
	mB.Deserialize(mA_proto);
	mB.Print("mB");

	size_t serialSize = mA_proto.ByteSizeLong();
	CHECK(serialSize <= 8);

	CHECK(mA.a == mB.a);
	CHECK(mA.b == mB.b);
	CHECK(mA.c == mB.c);
	CHECK(mA.x == mB.x);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Material_Class)
{
	
}

// ---  End of File ---
