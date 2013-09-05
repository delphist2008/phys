#ifndef VEC2DH
#define VEC2DH

#include <math.h>

class vec2 
{
    public:
        vec2();
        vec2(float, float);
		vec2(vec2&);
        bool operator==(vec2 rhs);
        vec2 operator+(vec2 rhs);
        vec2 operator-(vec2 rhs);
        vec2 operator*(vec2 rhs);
        vec2 operator/(vec2 rhs);
        vec2 operator+(float scalar);
        vec2 operator-(float scalar);
        vec2 operator*(float scalar);
        vec2 operator/(float scalar);
		friend vec2& operator+=(vec2& left,  vec2& right);
		friend vec2& operator-=(vec2& left,  vec2& right);
		friend vec2& operator/=(vec2& left,  vec2& right);
		friend vec2& operator*=(vec2& left,  vec2& right);
		friend vec2& operator/=(vec2& left,  float);
		friend vec2& operator*=(vec2& left,  float);
		friend vec2& operator+=(vec2& left,  float);
		friend vec2& operator-=(vec2& left,  float);
        float cross(vec2 rhs);
        float dot(vec2 rhs);
        float length();
        float x;
        float y;
};
#endif //VEC2DH