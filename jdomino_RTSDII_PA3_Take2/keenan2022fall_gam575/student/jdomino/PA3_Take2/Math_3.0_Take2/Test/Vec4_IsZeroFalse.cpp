//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"
using namespace Azul;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST(Vec4_IsZeroFalse, TestConfig::ALL)
{
#if Vec4_IsZeroFalse

	bool bvalue1;
	Vec4 v1(0.023f, 0.0f, 0.0f, 0.05f);

	CHECK(v1[x] == 0.023f);
	CHECK(v1[y] == 0.0f);
	CHECK(v1[z] == 0.0f);
	CHECK(v1[w] == 0.05f);

	bvalue1 = v1.isZero(0.0f);

	CHECK(bvalue1 == false);

	CHECK(v1[x] == 0.023f);
	CHECK(v1[y] == 0.0f);
	CHECK(v1[z] == 0.0f);
	CHECK(v1[w] == 0.05f);

#endif
} TEST_END

// ---  End of File ---------------
