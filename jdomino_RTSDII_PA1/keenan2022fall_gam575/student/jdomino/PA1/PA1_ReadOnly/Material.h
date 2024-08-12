//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Material.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Material
{
public:
	enum class Color
	{
		Blue = 0,  // needs to match .proto
		White,
		Red,
		Yellow
	};

public:
	Material() = default;
	Material(const Material &) = default;
	Material &operator = (const Material &) = default;
	~Material() = default;

	Material(Color a, Color b, Color c, int x);

	// Serialization 
	void Serialize(Material_proto &out) const;
	void Deserialize(const Material_proto &in);

	void Print(const char *const pName) const;
	const char *GetString(Color c) const;

public:
	int x;
	Color a;
	Color b;
	Color c;

};

#endif

// --- End of File ---
