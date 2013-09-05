#include "vec2d.h"

vec2::vec2()
{
	x = y = 0.0;
}

vec2::vec2(float _x, float _y)
{
	x = _x;
	y = _y;
}

vec2::vec2(vec2& cp)
{
	x = cp.x;
	y = cp.y;
}

bool vec2::operator==(vec2 rhs) {
	return(fabs(x - rhs.x)<0.000001 && fabs(y - rhs.y)<0.000001);
}

vec2 vec2::operator+(vec2 rhs) 
{
	return vec2( x + rhs.x, y + rhs.y );
}

vec2 vec2::operator-(vec2 rhs) 
{
	return vec2( x - rhs.x, y - rhs.y );
}

vec2 vec2::operator*(vec2 rhs) 
{
	return vec2( x * rhs.x, y * rhs.y );
}

vec2 vec2::operator/(vec2 rhs) 
{
	return vec2( x / rhs.x, y / rhs.y );
}

vec2 vec2::operator/(float scalar)
{
    return vec2(x / scalar, y / scalar);
}

vec2 vec2::operator*(float scalar)
{
    return vec2(x * scalar, y * scalar);
}

vec2 vec2::operator+(float scalar)
{
    return vec2(x + scalar, y + scalar);
}

vec2 vec2::operator-(float scalar)
{
    return vec2(x - scalar, y - scalar);
}

float vec2::dot(vec2 rhs) 
{
    return (x * rhs.x + y * rhs.y);
}

float vec2::cross(vec2 rhs) 
{
    return  x * rhs.y - y * rhs.x;
}

float vec2::length() 
{
    return float(sqrt( x*x + y*y));
}

vec2& operator+=(vec2& left,  vec2& right) 
{
	left = left + right;
    return left;
}

vec2& operator*=(vec2& left,  vec2& right) 
{
	left = left * right;
    return left;
}

vec2& operator/=(vec2& left,  vec2& right) 
{
	left = left / right;
    return left;
}

vec2& operator-=(vec2& left,  vec2& right) 
{
	left = left - right;
    return left;
}

vec2& operator/=(vec2& left, float right) 
{
	left = left / right;
    return left;
}

vec2& operator*=(vec2& left, float right) 
{
	left = left * right;
    return left;
}

vec2& operator+=(vec2& left, float right) 
{
	left = left + right;
    return left;
}

vec2& operator-=(vec2& left, float right) 
{
	left = left - right;
    return left;
}