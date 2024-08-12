//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "testData.h"

testData::~testData()
{

}

testData::testData(unsigned int val)
{
	this->x = val;
}

testData::testData()
{
	this->x = 0;
}

testData::testData(const testData &r)
{
	this->x = r.x;
}


void testData::Serialize(testData_proto &out) const
{
	out.set_x_val(this->x);
}

void testData::Deserialize(const testData_proto &in)
{
	this->x = in.x_val();
}

// --- End of File ---


