//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VECT3_H
#define ENGINE_MATH_VECT3_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Constants.h"
#include "Vec3Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat3;
	class Vec4;
	class Quat;

	// -----------------------------------------------------------
	// 
	// Vec3 
	//   True 3 element vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//     the "w" component is ignored and not set
	//                         
	//   v3  = | x  y  z  - | 
	//     
	// -----------------------------------------------------------

	class Vec3 final : public Align16
	{
	public:

		// Do your magic here

			// sample of my protos
			
			// Forces User to explicitly do the cast or constructor call with explicit
			//explicit Vec3(const Vec4 &v);
	                //Vec3 &operator=(const Vec4 &v);

			// Bracket
			//float &operator[] (const enum x_enum);
			//const float operator[] (const enum x_enum) const;
			//
			// Accessors - Robin's suggestion
			//void x(const float v);
			//const float x() const;

			// scale operators
			//Vec3 operator * (const float scale) const;
			//friend Vec3 operator *(const float scale, const Vec3 &inV);
			//void operator *= (const float scale);

			// Vec3 * Mat3
			//Vec3 operator* (const Mat3 &m) const;
			//Vec3 operator*= (const Mat3 &m);

			// Vector functions
			//const Vec3 cross(const Vec3 &vIn) const;
			//const Vec3Proxy len(void) const;

		Vec3();
		Vec3(const Vec3& inVec3);
		Vec3(const Vec4& inVec4);
		Vec3(const float x, const float y, const float z);
		const Vec3 operator = (const Vec3& inVec3);
		const Vec3 operator = (const Vec4& inVec4);
		~Vec3();

		void set(float x, float y, float z);
		void set(Vec3 inVec3);
		void set(Vec4 inVec4);

		// Add
		Vec3 operator + (Vec3 inVec3);
		Vec3 operator + (float inFloat);
		friend Vec3 operator + (float inFloat, Vec3 inVec3);

		// Subtract
		Vec3 operator - (Vec3 inVec3) const;
		Vec3 operator - (float inFloat) const;
		friend Vec3 operator - (float inFloat, Vec3 inVec3);

		// Multiply
		Vec3 operator * (Vec3 inVec3) const;
		Vec3 operator * (float inFloat) const;
		Vec3 operator * (Quat inQ) const;
		friend Vec3 operator * (float inFloat, Vec3 inVec3);
		const Vec3 operator *=(float inFloat);
		Vec3 operator *= (Quat inQ);

		Vec3 operator += (const Vec3 inVec3);
		Vec3 operator -= (const Vec3 inVec3);


		//Unary Minus Overload
		Vec3 operator-();

		//Unary Plus Overload
		Vec3 operator+();


		//Cross Product
		Vec3 cross(Vec3 inVec3) const;

		//Dot Product
		float dot(const Vec3& inVec3) const;

		//Angle
		float getAngle(Vec3 inVec3);

		//Normalized Vec3or
		Vec3 norm();
		Vec3 getNorm();
		//float mag();
		Vec3Proxy mag();

		float len();

		//friend bool operator==(float inFloat1, float inFloat2);

		//Vec3 * Mat4 operator overloader
		friend Vec3& operator *(Vec3 inVec3, Mat3 inMat3);

		Vec3 operator *=(Mat3 inMat3);

		//[] overloads GET
		const float operator[](const x_enum inX) const;
		const float operator[](const y_enum inY) const;
		const float operator[](const z_enum inZ) const;
		//const float operator[](const w_enum inW) const;

		//[] overloads SET
		float& operator[](const x_enum);
		float& operator[](const y_enum);
		float& operator[](const z_enum);
		//float& operator[](const w_enum);


		//XYZW GET
		const float& x() const;
		const float& y() const;
		const float& z() const;
		//const float& w() const;

		//XYZW SET
		float& x();
		float& y();
		float& z();
		//float& w();

		void x(float inX);
		void y(float inY);
		void z(float inZ);

		bool isEqual(Vec3 inVec3, float epsilon = 0);
		bool isZero(float epsilon = 0);

		// for printing
		void Print(const char *pName) const;

	private:

		friend Mat3;
		friend Vec4;
		friend Quat;

		union
		{
			/*                          */
			/*   v3  = | x  y  z  - |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				
			};
		};
	};
}

#endif

//--- End of File ---
