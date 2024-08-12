//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_Matrix_4x4_H
#define ENGINE_MATH_Matrix_4x4_H

#include "Vec4.h"
#include "Vec3.h"
#include "Debug.h"

namespace Azul
{

	class Mat4 final : public Align16
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Trans
		{
			XYZ
		};

		enum class Scale
		{
			XYZ
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

		enum class Row
		{
			i0,
			i1,
			i2,
			i3
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

		enum class Hint
		{
			GeneralizeMat4 = 0x0,  // generalize 4x4 inverse  (no flags)
			Rot = 0x1,               // Mat4 inverse is M.T()
			Trans = 0x2,             // Mat4 inverse is M(-trans)
			RotTrans = 0x3,          // rot and trans  A_inv is A.T() 
			Scale = 0x4,             // Mat4 invers is M(1/scale)
			RotScale = 0x5,          // Rot and Scale no translate
			TransScale = 0x6,        // Trans and Scale no Translate
			GeneralizedAffine = 0x7  // generalize Affine
		};

	public:

		// Do your magic here

				// Sample of my protos
				
				//Mat4(const Trans, const float tx, const float ty, const float tz);
				//explicit Mat4(const Special type);

				// Set 
				//void set(const Row type, const Vec4 &V);

				// bracket operators	
				//float &operator[] (const enum m0_enum);
				//const float operator[] (const enum m0_enum) const;

				// Accessor	
				//void m0( const float v);
				//const float m0() const;

				// Comparison
				//const bool isRotation(const float epsilon = MATH_TOLERANCE) const;

				// Scale operators
				//Mat4 operator * (const float s) const;
				//friend Mat4 operator *(const float scale, const Mat4 &A);
				//void operator *= (const float scale);

				//big 4
		Mat4();
		Mat4(const Mat4& inMat4);
		//Specialized Constructor
		Mat4(Vec4 vA, Vec4 vB, Vec4 vC, Vec4 vD);
		const Mat4& operator = (const Mat4& inMat4);
		~Mat4();

		//Transpose Constructors
		Mat4 T();
		Mat4 getT();

		//Special Constructor
		Mat4(Mat4::Special special);

		//Trans Constructor
		Mat4(Mat4::Trans tran, float in1, float in2, float in3);
		Mat4(Mat4::Trans tran, Vec4 inVec4);

		//Scale Constructor
		Mat4(Mat4::Scale scale, float in1, float in2, float in3);
		Mat4(Mat4::Scale scale, Vec4 inVec4);

		//Rot Constructor
		//Mat4(Mat4::Rot rot);
		Mat4(Mat4::Rot rot, Vec4& inVec4, float inFloat);
		Mat4(Mat4::Rot1 rot, float inFloat);
		Mat4(Mat4::Rot3 rot, float inFloatX, float inFloatY, float inFloatZ);


		//M*M
		Mat4 operator* (Mat4 inMat4);
		Mat4 operator *= (Mat4 inMat4);

		//M+M
		Mat4 operator+ (Mat4 inMat4);
		Mat4 operator+=(Mat4 inMat4);

		//M-M
		Mat4 operator- (Mat4 inMat4);
		Mat4 operator-= (Mat4 inMat4);

		//Unary Plus
		Mat4 operator+();

		//Unary Minus
		Mat4 operator-();

		//Scale
		friend Mat4 operator* (float inFloat, Mat4 inMat4);
		friend Mat4 operator* (Mat4 inMat4, float inFloat);
		friend Mat4 operator/ (Mat4 inMat4, float inFloat);
		Mat4 operator*=(float inFloat);

		void SetMs(Vec4& inVec4);

		//Special Set
		void set(Mat4::Special type);

		//Trans Set
		void set(Mat4::Trans type, float in1, float in2, float in3);
		void set(Mat4::Trans type, Vec4 inVec4);

		//Scale Set
		void set(Mat4::Scale type, float in1, float in2, float in3);
		void set(Mat4::Scale type, Vec4 inVec4);

		//Row Set
		void set(Mat4::Row row, Vec4 inVec4);

		//Row Get
		Vec4 get(Mat4::Row row);

		//Rot Set
		void set(Mat4::Rot rot, Vec4& inVec4, float inFloat);
		void set(Mat4::Rot1 rot, float inFloat);
		void set(Mat4::Rot3 rot, float in1, float in2, float in3);

		//Orient Set
		void set(Mat4::Orient orientType, Vec4 inVec41, Vec4 inVec42);

		//Determinant
		float det();

		//Inverse
		Mat4 inv();

		//Orient
		Mat4(Mat4::Orient orientType, Vec4 inVec41, Vec4 inVec42);

		void privSetRotOrient(Vec4& v1, Vec4& v2);
		void privSetRotInverseOrient();

		//Vec4 Set
		void set(Vec4 inVec41, Vec4 inVec42, Vec4 inVec43, Vec4 inVec44);

		//M == M
		bool isEqual(Mat4 inMat4);

		//Identity bool
		bool isIdentity(float tolerance = 0);

		//Rotation bool
		bool isRotation();

		//Inverse Mat4
		Mat4 getInv();
		Mat4 getAdjoint();
		float subMDet(float inX1, float inX2, float inX3, float inY1, float inY2, float inY3, float inZ1, float inZ2, float inZ3);



		Vec4& GetV0();
		Vec4& GetV1();
		Vec4& GetV2();
		Vec4& GetV3();

		//Mat4 GETs
		const float m0() const;
		const float m1() const;
		const float m2() const;
		const float m3() const;
		const float m4() const;
		const float m5() const;
		const float m6() const;
		const float m7() const;
		const float m8() const;
		const float m9() const;
		const float m10() const;
		const float m11() const;
		const float m12() const;
		const float m13() const;
		const float m14() const;
		const float m15() const;

		float& m0();
		float& m1();
		float& m2();
		float& m3();
		float& m4();
		float& m5();
		float& m6();
		float& m7();
		float& m8();
		float& m9();
		float& m10();
		float& m11();
		float& m12();
		float& m13();
		float& m14();
		float& m15();

		const float operator[](m0_enum) const;
		const float operator[](m1_enum) const;
		const float operator[](m2_enum) const;
		const float operator[](m3_enum) const;
		const float operator[](m4_enum) const;
		const float operator[](m5_enum) const;
		const float operator[](m6_enum) const;
		const float operator[](m7_enum) const;
		const float operator[](m8_enum) const;
		const float operator[](m9_enum) const;
		const float operator[](m10_enum) const;
		const float operator[](m11_enum) const;
		const float operator[](m12_enum) const;
		const float operator[](m13_enum) const;
		const float operator[](m14_enum) const;
		const float operator[](m15_enum) const;

		float& operator[](m0_enum);
		float& operator[](m1_enum);
		float& operator[](m2_enum);
		float& operator[](m3_enum);
		float& operator[](m4_enum);
		float& operator[](m5_enum);
		float& operator[](m6_enum);
		float& operator[](m7_enum);
		float& operator[](m8_enum);
		float& operator[](m9_enum);
		float& operator[](m10_enum);
		float& operator[](m11_enum);
		float& operator[](m12_enum);
		float& operator[](m13_enum);
		float& operator[](m14_enum);
		float& operator[](m15_enum);

		// For printing
		void Print(const char *pName) const;

	private:

		friend Mat3;
		friend Vec3;
		friend Vec4;

		union
		{
			/*     | m0  m1  m2   m3  | */
			/* m = | m4  m5  m6   m7  | */
			/*     | m8  m9  m10  m11 | */
			/*     | m12 m13 m14  m15 | */

			struct
			{
				Vec4 _rows[4];
			};


			struct
			{
				Vec4 _v0;
				Vec4 _v1;
				Vec4 _v2;
				Vec4 _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#endif

//--- End of File ---
