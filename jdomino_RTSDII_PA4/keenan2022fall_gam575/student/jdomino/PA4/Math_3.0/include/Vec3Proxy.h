//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VEC3_PROXY_H
#define ENGINE_MATH_VEC3_PROXY_H

namespace Azul
{
	// Vector related proxies here:

	struct Vec3Proxy
	{
	public:
		// sample
		// 
		//   Vec3Proxy(float a, float b, float c);
		//	 operator float() const;
		//   bool operator > (const Vec3Proxy &r) const;

        Vec3Proxy()
        {
            this->x = 0; //everything 0's and w is 1
            this->y = 0;
            this->z = 0;
            //this->w = 1;
        }

        Vec3Proxy(float a, float b, float c)
            :x(a), y(b), z(c)
        {

        }

        //coversion operator
        operator float()
        {
            //converts the current Proxy to its length - only called if not using a comparison operator
            return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
        }
        //comparison operators
                //is equal to
        bool operator == (const Vec3Proxy& r)
        {
            //return whether or not the x y and z are the same
            return (this->x == r.x && this->y == r.y && this->z == r.z);
        }

        //is not equal to
        bool operator != (const Vec3Proxy& r)
        {
            //return whether or not the x y and z are the same
            return !(this->x == r.x && this->y == r.y && this->z == r.z);
        }

        //greater than
        bool operator > (const Vec3Proxy& r)
        {
            return ((this->x * this->x + this->y * this->y + this->z * this->z) > (r.x * r.x + r.y * r.y + r.z * r.z));
        }

        //greater than or equal to
        bool operator >= (const Vec3Proxy& r)
        {
            return ((this->x * this->x + this->y * this->y + this->z * this->z) >= (r.x * r.x + r.y * r.y + r.z * r.z));
        }
        //less than
        bool operator < (const Vec3Proxy& r)
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z <
                (r.x* r.x + r.y * r.y + r.z * r.z));
        }
        //less than or equal to
        bool operator <= (const Vec3Proxy& r)
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z <=
                (r.x * r.x + r.y * r.y + r.z * r.z));
        }


	private:
		float x;
		float y;
		float z;
	};

}

#endif

//--- End of File ---
