//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Texture.h"
#include "Texture.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

TEST_WITH_TEARDOWN(Texture_Class, TestConfig::ALL)
{
#if Texture_Class

	Trace::out("\n");

	CHECK(sizeof(Texture) == 8);

	unsigned char pDataA[]{0x12, 0x34, 0x56, 0x78, 0xff, 0xee, 0xdd, 0xcc, 0x99, 0x88};
	unsigned int DataASize = sizeof(pDataA) / sizeof(char);

	Texture tA((char *)&pDataA[0], DataASize);
	tA.Print("tA");

	CHECK((unsigned char)tA.poData[0] == 0x12);
	CHECK((unsigned char)tA.poData[1] == 0x34);
	CHECK((unsigned char)tA.poData[2] == 0x56);
	CHECK((unsigned char)tA.poData[3] == 0x78);
	CHECK((unsigned char)tA.poData[4] == 0xff);
	CHECK((unsigned char)tA.poData[5] == 0xee);
	CHECK((unsigned char)tA.poData[6] == 0xdd);
	CHECK((unsigned char)tA.poData[7] == 0xcc);
	CHECK((unsigned char)tA.poData[8] == 0x99);
	CHECK((unsigned char)tA.poData[9] == 0x88);

	CHECK( tA.DataSize == 10 );

	Texture_proto tA_proto;
	tA.Serialize(tA_proto);

	Texture tB;
	tB.Deserialize(tA_proto);
	tB.Print("tB");

	size_t serialSize = tA_proto.ByteSizeLong();
	CHECK(serialSize <= 14);
	
	CHECK(tB.poData != nullptr);

	CHECK((unsigned char)tA.poData[0] == (unsigned char)tB.poData[0]);
	CHECK((unsigned char)tA.poData[1] == (unsigned char)tB.poData[1]);
	CHECK((unsigned char)tA.poData[2] == (unsigned char)tB.poData[2]);
	CHECK((unsigned char)tA.poData[3] == (unsigned char)tB.poData[3]);
	CHECK((unsigned char)tA.poData[4] == (unsigned char)tB.poData[4]);
	CHECK((unsigned char)tA.poData[5] == (unsigned char)tB.poData[5]);
	CHECK((unsigned char)tA.poData[6] == (unsigned char)tB.poData[6]);
	CHECK((unsigned char)tA.poData[7] == (unsigned char)tB.poData[7]);
	CHECK((unsigned char)tA.poData[8] == (unsigned char)tB.poData[8]);
	CHECK((unsigned char)tA.poData[9] == (unsigned char)tB.poData[9]);

	CHECK(tA.DataSize == tB.DataSize);

	unsigned char pDataC[]{0x71, 0xCD, 0xEF, 0xC1, 0x5F};
	unsigned int DataCSize = sizeof(pDataC) / sizeof(char);

	Texture tC((char *)&pDataC[0], DataCSize);
	tC.Print("tC");

	CHECK((unsigned char)tC.poData[0] == 0x71);
	CHECK((unsigned char)tC.poData[1] == 0xcd);
	CHECK((unsigned char)tC.poData[2] == 0xef);
	CHECK((unsigned char)tC.poData[3] == 0xc1);
	CHECK((unsigned char)tC.poData[4] == 0x5f);

	CHECK(tC.DataSize == 5);

	Texture_proto tC_proto;
	tC.Serialize(tC_proto);

	Texture tD;
	tD.Deserialize(tC_proto);
	tD.Print("tD");

	serialSize = tC_proto.ByteSizeLong();
	CHECK(serialSize <= 9);

	CHECK((unsigned char)tC.poData[0] == (unsigned char)tD.poData[0]);
	CHECK((unsigned char)tC.poData[1] == (unsigned char)tD.poData[1]);
	CHECK((unsigned char)tC.poData[2] == (unsigned char)tD.poData[2]);
	CHECK((unsigned char)tC.poData[3] == (unsigned char)tD.poData[3]);
	CHECK((unsigned char)tC.poData[4] == (unsigned char)tD.poData[4]);

	CHECK(tC.DataSize == tD.DataSize);

	Trace::out("\n");

#endif
} TEST_END

TEST_TEARDOWN(Texture_Class)
{

}

// ---  End of File ---
