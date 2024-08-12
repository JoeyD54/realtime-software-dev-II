//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_Vec4D_H
#define ENGINE_MATH_Vec4D_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Constants.h"
#include "Vec4Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat4;
	class Mat3;
	class Vec3;

	// -----------------------------------------------------------
	// 
	// Vec4 
	//   True 4 element Vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//                         
	//   v4  = | x  y  z  w | 
	//     
	// -----------------------------------------------------------

	class Vec4 final : public Align16
	{
	public:

	    // Do your magic here

		// sample of my protos

		// Constructors
		// Vec4(const float in_x, const float in_y, const float in_z, const float in_w);

		// Forces User to explicitly do the cast or constructor call with explicit
		// Vec4(const Vec3 &v, const float w = 1.0f);

		// Bracket
		// float &operator[] (const enum x_enum);
		// const float operator[] (const enum x_enum) const;

		// Accessors - Robin's suggestion
		// void x(const float v);
		// const float x()const;

		// scale operators
		// Vec4 operator * (const float scale) const;
		// friend Vec4 operator *(const float scale, const Vec4 &inV);
		// void operator *= (const float scale);

		// Vec4 * Mat4
		// Vec4 operator * (const Mat4 &m) const;
		// Vec4 operator *= (const Mat4 &m);

		// (Vec3,1) * Mat4
        // friend Vec4 operator *(const Vec3 &v, const Mat4 &m);
        // friend Vec4 operator *= (const Vec3 &v, const Mat4 &m);

		// Vec4 functions
		// const Vec4Proxy len() const;

		// set
		// void set(const Vec4 &A);
		// void set(const Vec3 &v, const float w = 1.0f);

		// comparison
		// bool isEqual(const Vec4 &v, const float epsilon = MATH_TOLERANCE) const;
	
		Vec4();
		Vec4(const Vec4& inVec4);
		Vec4(const float x, const float y, const float z, const float w = 1);
		const Vec4 operator = (const Vec4& inVec4);
		~Vec4();

		void set(float x, float y, float z, float w = 1);
		void set(Vec4 inVec4);

		// Add
		Vec4 operator + (Vec4 inVec4);
		Vec4 operator + (float inFloat);
		friend Vec4 operator + (float inFloat, Vec4 inVec4);

		// Subtract
		Vec4 operator - (Vec4 inVec4) const;
		Vec4 operator - (float inFloat) const;
		friend Vec4 operator - (float inFloat, Vec4 inVec4);

		// Multiply
		Vec4 operator * (Vec4 inVec4) const;
		Vec4 operator * (float inFloat) const;
		friend Vec4 operator * (float inFloat, Vec4 inVec4);
		const Vec4 operator *=(float inFloat);

		Vec4 operator += (const Vec4 inVec4);
		Vec4 operator -= (const Vec4 inVec4);


		//Unary Minus Overload
		Vec4 operator-();

		//Unary Plus Overload
		Vec4 operator+();


		//Cross Product
		Vec4 cross(Vec4 inVec4) const;

		//Dot Product
		float dot(Vec4 inVec4);

		//Angle
		float getAngle(Vec4 inVec4);

		//Normalized Vec4or
		Vec4 norm();
		Vec4 getNorm();
		//float mag();
		Vec4Proxy mag();



		//friend bool operator==(float inFloat1, float inFloat2);

		//Vec4 * Matrix operator overloader
		friend Vec4& operator *(Vec4 inVec4, Mat4 inMat4);

		Vec4 operator *=(Mat4 inMat4);

		//[] overloads GET
		const float operator[](const x_enum inX) const;
		const float operator[](const y_enum inY) const;
		const float operator[](const z_enum inZ) const;
		const float operator[](const w_enum inW) const;

		//[] overloads SET
		float& operator[](const x_enum);
		float& operator[](const y_enum);
		float& operator[](const z_enum);
		float& operator[](const w_enum);


		//XYZW GET
		const float& x() const;
		const float& y() const;
		const float& z() const;
		const float& w() const;

		//XYZW SET
		float& x();
		float& y();
		float& z();
		float& w();

		bool isEqual(Vec4 inVec4, float epsilon = 0);
		bool isZero(float epsilon = 0);

		// for printing
		void Print(const char *pName) const;

	private:

		friend Mat4;
		friend Mat3;
		friend Vec3;

		union
		{
			/*                          */
			/*   v4  = | x  y  z  w |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				float _vw;
			};
		};
	};

	Vec4 operator* (const Vec3 &v, const Mat4 &m);
	Vec4 operator*= (const Vec3 &v, const Mat4 &m);
}

#endif

//--- End of File ---
