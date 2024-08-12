//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_VEC4_PROXY_H
#define ENGINE_MATH_VEC4_PROXY_H

namespace Azul
{
	// Vector related proxies here:

	struct Vec4Proxy
	{
	public:
		//Vec4Proxy(float a, float b, float c, float d);
		//operator float() const;
		//bool operator > (const Vec4Proxy &r) const;

        Vec4Proxy()
        {
            this->x = 0; //everything 0's and w is 1
            this->y = 0;
            this->z = 0;
            this->w = 1;
        }

        Vec4Proxy(float a, float b, float c, float d = 1)
            :x(a), y(b), z(c), w(d)
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
        bool operator == (const Vec4Proxy& r)
        {
            //return whether or not the x y and z are the same
            return (this->x == r.x && this->y == r.y && this->z == r.z && this->w == r.w);
        }

        //is not equal to
        bool operator != (const Vec4Proxy& r)
        {
            //return whether or not the x y and z are the same
            return !(this->x == r.x && this->y == r.y && this->z == r.z && this->w == r.w);
        }

        //greater than
        bool operator > (const Vec4Proxy& r)
        {
            return ((this->x * this->x + this->y * this->y + this->z * this->z) > (r.x * r.x + r.y * r.y + r.z * r.z));
        }

        //greater than or equal to
        bool operator >= (const Vec4Proxy& r)
        {
            return ((this->x * this->x + this->y * this->y + this->z * this->z) >= (r.x * r.x + r.y * r.y + r.z * r.z));
        }
        //less than
        bool operator < (const Vec4Proxy& r)
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z <
                (r.x* r.x + r.y * r.y + r.z * r.z));
        }
        //less than or equal to
        bool operator <= (const Vec4Proxy& r)
        {
            return (this->x * this->x + this->y * this->y + this->z * this->z <=
                (r.x * r.x + r.y * r.y + r.z * r.z));
        }

	private:
		float x;
		float y;
		float z;
		float w;
	};

}

#endif

//--- End of File ---
