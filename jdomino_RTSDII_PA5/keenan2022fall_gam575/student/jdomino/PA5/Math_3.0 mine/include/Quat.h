//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Mat4.h"
#include "Debug.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace Azul
{
	class Quat final : public Align16
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

        // add magic

		//Big4
		Quat();
		Quat(const Quat& inQuat);
		Quat& operator = (const Quat& inQuat);
		~Quat();

		Quat(float F1, float F2, float F3, float F4);
		Quat(Vec3 inVec, float F1);
		Quat(Special special);
		Quat(Mat4 inMat);
		Quat(Quat::Rot rot, Vec3 inV3, float inF);
		Quat(Quat::Rot3 rot, float inX, float inY, float inZ);
		
		Quat(Quat::Rot1 rot, float inF);

		Quat(Quat::Orient orient, Vec3 in1V3, Vec3 in2V3);

		void set(float x, float y, float z, float w = 1);
		void set(Quat inQ);
		void set(Mat4 M);		
		void set(Special special);
		void set(Quat::Rot1 rot, float inF);		
		void set(Quat::Rot rot, Vec3 inV3, float inF);
		void set(Quat::Rot3 rot, float inX, float inY, float inZ);
		void set(Quat::Orient orient, Vec3 in1V3, Vec3 in2V3);

		// Add
		Quat operator + (Quat inQ);
		Quat operator + (float inFloat);

		// Subtract
		Quat operator - (Quat inQ) const;
		Quat operator - (float inFloat) const;

		// Multiply
		Quat operator * (Quat inQ) const;
		Quat operator * (float inFloat) const;
		
		//Divide
		Quat operator / (Quat inQ) const;
		Quat operator / (float inFloat) const;

		Quat operator += (const Quat inQ);
		Quat operator -= (const Quat inQ);

		Quat operator += (const float inF);
		Quat operator -= (const float inF);

		Quat operator *= (const Quat inQ);
		Quat operator /= (const Quat inQ);

		Quat operator *= (const float inF);
		Quat operator /= (const float inF);


		friend Quat operator + (float inFloat, Quat inQ);
		friend Quat operator - (float inFloat, Quat inQ);

		friend Quat operator * (float inFloat, Quat inQ);
		friend Quat operator / (float inFloat, Quat inQ);


		Quat operator-();
		Quat operator+();

		void Lqcvq(const Vec3& inV3, Vec3& outV3) const;
		void Lqvqc(const Vec3& inV3, Vec3& outV3) const;

		Quat getConj();
		Quat conj();

		Quat getT();
		Quat T();

		Quat inv();
		Quat getInv();
		Quat cross(Quat inQ) const;
		float dot(Quat inQ);
		Quat norm();
		Quat getNorm();

		void getAxis(Vec3& outV3);
		float getAngle();
		Quat axisAngle();

		void set(Vec3 inVec, float F1);

		void getVec3(Vec3& setVec);
		Vec3 setVec3();
		void setVec3(Vec3& setVec);

		void getVec4(Vec4& setVec);
		Vec4 setVec4();
		void setVec4(Vec4& setVec);

		float mag();
		float magSquared();
		float invMag();
		float len();

		Vec3 getVec3();

		bool isEqual(Quat inQ, float tolerance);
		bool isNegEqual(Quat inQ, float tolerance);
		bool isZero(float tolerance);
		bool isNormalized(float tolerance);
		bool isEquivalent(Quat inQ, float tolerance);
		bool isIdentity(float tolerance);
		bool isConjugateEqual(Quat inQ, float tolerance);

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
		const float& qx() const;
		const float& qy() const;
		const float& qz() const;
		const float& qw() const;
		const float& real() const;

		//XYZW SET
		float& qx();
		float& qy();
		float& qz();
		float& qw();
		float& real();


		//XYZW SET
		void qx(float inX);
		void qy(float inY);
		void qz(float inZ);
		void qw(float inW);
		void real(float inW);

	private:
		friend Vec4;
		friend Mat4;

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};

			struct
			{
				Vec3  _qV3;
			};

			struct
			{
				Vec4 _qV4;
			};
		};

	};
}

#endif 

//--- End of File ---
