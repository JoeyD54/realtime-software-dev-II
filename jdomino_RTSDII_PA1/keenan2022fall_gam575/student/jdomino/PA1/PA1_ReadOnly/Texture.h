//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Texture.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Texture
{
public:
	Texture() = default;
	Texture(const Texture &) = delete;
	Texture &operator = (const Texture &) = delete;
	~Texture();

	Texture(char *pInData, unsigned int DataSize);

	// Serialization 
	void Serialize(Texture_proto &out) const;
	void Deserialize(const Texture_proto &in);

	void Print(const char *const pName) const;

public:
	char *poData;
	unsigned int DataSize;
};

#endif

// --- End of File ---
