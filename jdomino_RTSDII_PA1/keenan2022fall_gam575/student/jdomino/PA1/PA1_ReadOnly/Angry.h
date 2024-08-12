//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef ANGRY_H
#define ANGRY_H

#include "Angry.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Angry
{
public:
	static const unsigned int N = 4;

public:
	Angry() = default;
	Angry(const Angry &) = default;
	Angry &operator = (const Angry &) = default;
	~Angry() = default;

	Angry(int x0, int x1, int x2, int x3, float value);

	// Serialization 
	void Serialize(Angry_proto &out) const;
	void Deserialize(const Angry_proto &in);

	void Print(const char *const pName) const;

public:
	int arr[N];
	float value;

};

#endif

// --- End of File ---
