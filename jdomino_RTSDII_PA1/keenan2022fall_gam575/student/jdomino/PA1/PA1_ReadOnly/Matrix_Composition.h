//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MATRIX_COMPOSITION_H
#define MATRIX_COMPOSITION_H

#include "Matrix_Composition.pb.h"
#include "Vect.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Matrix_Composition
{
public:
	Matrix_Composition() = default;
	Matrix_Composition(const Matrix_Composition &) = default;
	Matrix_Composition &operator = (const Matrix_Composition &) = default;
	~Matrix_Composition() = default;

	Matrix_Composition(Vect &v0, Vect &v1, Vect &v2, Vect &v3);
	Matrix_Composition(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);

	// Serialization 
	void Serialize(Matrix_Composition_proto &out) const;
	void Deserialize(const Matrix_Composition_proto &in);

	void Print(const char *const pName) const;

public:
	Vect v0;
	Vect v1;
	Vect v2;
	Vect v3;

};

#endif

// --- End of File ---

