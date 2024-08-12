//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_TRIG_H
#define ENGINE_MATH_TRIG_H

namespace Azul
{
	class Trig
	{
	public:

		// Freebie... get it started
		static float sqrt(const float val);
		static float sqrtf(float val);
		static float rsqrt(float val);
		static float cos(float val);
		static float acos(float val);
		static float sin(float val);
		static float asin(float val);
		static void cossin(float& outCos, float& outSin, float inX);
		static float tan(float val);
		static float atan(float val);
		static float atan2(float x, float y);
		// Do your magic here

	};
}

#endif

//--- End of File ---
