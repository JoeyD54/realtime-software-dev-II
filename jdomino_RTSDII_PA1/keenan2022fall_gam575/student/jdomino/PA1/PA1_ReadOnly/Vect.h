//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef VECT_H
#define VECT_H

#include "Vect.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Vect
{
public:
	Vect() = default;
	Vect(const Vect &) = default;
	Vect &operator = (const Vect &) = default;
	~Vect() = default;

	Vect(float x, float y, float z, float w);

	// Serialization 
	void Serialize(Vect_proto &out) const;
	void Deserialize(const Vect_proto &in);

	void Print(const char *const pName) const;

public:
	float x;
	float y;
	float z;
	float w;
};

#endif

// --- End of File ---

