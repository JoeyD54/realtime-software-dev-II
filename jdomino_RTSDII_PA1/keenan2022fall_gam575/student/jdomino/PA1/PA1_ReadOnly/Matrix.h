//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MATRIX_H
#define MATRIX_H

#include "Matrix.pb.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

class Matrix
{
public:
	Matrix() = default;
	Matrix(const Matrix &) = default;
	Matrix &operator = (const Matrix &) = default;
	~Matrix() = default;

	Matrix(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);

	// Serialization 
	void Serialize(Matrix_proto &out) const;
	void Deserialize(const Matrix_proto &in);

	void Print(const char *const pName) const;

public:
	float m0;
	float m1;
	float m2;
	float m3;
	float m4;
	float m5;
	float m6;
	float m7;
	float m8;
	float m9;
	float m10;
	float m11;
	float m12;
	float m13;
	float m14;
	float m15;

};

#endif

// --- End of File ---

