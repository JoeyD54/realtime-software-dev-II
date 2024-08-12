//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_Matrix_3x3_H
#define ENGINE_MATH_Matrix_3x3_H

#include "Vec4.h"
#include "Debug.h"
#include "Mat4.h"

namespace Azul
{

	class Mat3 final : public Align16
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Row
		{
			i0,
			i1,
			i2
		};

	public:

		// Do your magic here

		// Sample of my protos
			
			// bracket operators	
			//float &operator[] (const enum m0_enum);
			//const float operator[] (const enum m0_enum) const;
			
			// Accessor	
			//void m0(const float v);
			//const float m0() const;
			
			// Comparison
			//bool isEqual(const Matrix &A, const float epsilon = MATH_TOLERANCE) const;

				//big 4
		Mat3();
		Mat3(const Mat3& inMat3);
		//Specialized Constructor
		Mat3(Vec4 vA, Vec4 vB, Vec4 vC, Vec4 vD);
		const Mat3& operator = (const Mat3& inMat3);
		~Mat3();

		//Transpose Constructors
		Mat3 T();
		Mat3 getT();

		//Special Constructor
		Mat3(Mat3::Special special);

		//Trans Constructor
		//Mat3(Mat3::Trans tran, float in1, float in2, float in3);
		//Mat3(Mat3::Trans tran, Vec4 inVec4);

		//Scale Constructor
		//Mat3(Mat3::Scale scale, float in1, float in2, float in3);
		//Mat3(Mat3::Scale scale, Vec4 inVec4);

		//Rot Constructor
		//Mat3(Mat3::Rot rot);
		//Mat3(Mat3::Rot rot, Vec4& inVec4, float inFloat);
		//Mat3(Mat3::Rot1 rot, float inFloat);
		//Mat3(Mat3::Rot3 rot, float inFloatX, float inFloatY, float inFloatZ);


		//M*M
		Mat3 operator* (Mat3 inMat3);
		Mat3 operator *= (Mat3 inMat3);

		//M+M
		Mat3 operator+ (Mat3 inMat3);
		Mat3 operator+=(Mat3 inMat3);

		//M-M
		Mat3 operator- (Mat3 inMat3);
		Mat3 operator-= (Mat3 inMat3);

		//Unary Plus
		Mat3 operator+();

		//Unary Minus
		Mat3 operator-();

		//Scale
		friend Mat3 operator* (float inFloat, Mat3 inMat3);
		friend Mat3 operator* (Mat3 inMat3, float inFloat);
		friend Mat3 operator/ (Mat3 inMat3, float inFloat);
		Mat3 operator*=(float inFloat);

		void SetMs(Vec4& inVec4);

		//Special Set
		void set(Mat3::Special type);

		//Trans Set
		//void set(Mat3::Trans type, float in1, float in2, float in3);
		//void set(Mat3::Trans type, Vec4 inVec4);

		//Scale Set
		//void set(Mat3::Scale type, float in1, float in2, float in3);
		//void set(Mat3::Scale type, Vec4 inVec4);

		//Row Set
		void set(Mat3::Row row, Vec4 inVec4);

		//Row Get
		Vec4 get(Mat3::Row row);

		//Rot Set
		//void set(Mat3::Rot rot, Vec4& inVec4, float inFloat);
		//void set(Mat3::Rot1 rot, float inFloat);
		//void set(Mat3::Rot3 rot, float in1, float in2, float in3);

		//Orient Set
		//void set(Mat3::Orient orientType, Vec4 inVec41, Vec4 inVec42);

		//Determinant
		float det();

		//Inverse
		Mat3 inv();

		//Orient
		//Mat3(Mat3::Orient orientType, Vec4 inVec41, Vec4 inVec42);

		void privSetRotOrient(Vec4& v1, Vec4& v2);
		void privSetRotInverseOrient();

		//Vec4 Set
		void set(Vec4 inVec41, Vec4 inVec42, Vec4 inVec43, Vec4 inVec44);

		//M == M
		bool isEqual(Mat3 inMat3);

		//Identity bool
		bool isIdentity(float tolerance = 0);

		//Rotation bool
		bool isRotation();

		//Inverse Mat3
		Mat3 getInv();
		Mat3 getAdjoint();
		float subMDet(float inX1, float inX2, float inX3, float inY1, float inY2, float inY3, float inZ1, float inZ2, float inZ3);



		Vec4& GetV0();
		Vec4& GetV1();
		Vec4& GetV2();
		Vec4& GetV3();

		//Mat3 GETs
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
		
		friend Mat4;
		friend Vec4;
		friend Vec4;

		union
		{
			/*     | m0  m1  m2   0 | */
			/* m = | m4  m5  m6   0 | */
			/*     | m8  m9  m10  0 | */
			/*     | 0   0   0    1 | */

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
