//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "testData.pb.h"

class testData
{

public:
	testData();
	testData(const testData &);
	testData &operator = (const testData &) = default;
	~testData();

	testData( unsigned int  val);

	
	// Serialization 
	void Serialize(testData_proto &out) const;
	void Deserialize(const testData_proto &in);


public:
	unsigned int x;

};

#endif

// --- End of File ---
