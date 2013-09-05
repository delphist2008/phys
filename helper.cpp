#include "helper.h"

double  area (vec2 a, vec2  b, vec2  c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double  area (float ax, float ay, float bx, float by, float cx, float cy) 
{
	return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

bool intersect_1 (float a, float b, float c, float d) 
{
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}

bool intersect (vec2  a, vec2  b, vec2  c, vec2  d)  
{
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a,b,c) * area(a,b,d) <= 0
		&& area(c,d,a) * area(c,d,b) <= 0;
}

bool intersect (float  ax, float ay,  float  bx, float by, float cx, float cy, float dx, float dy)
{
	return intersect_1 (ax, bx, cx, dx)
		&& intersect_1 (ay, by, cy, dy)
		&& area(ax, ay, bx, by, cx, cy) * area(ax, ay, bx, by,dx, dy) <= 0
		&& area(cx, cy, dx, dy, ax, ay) * area(cx, cy, dx, dy, bx, by) <= 0;
}

vec2 v0, v1, v2;
float dot00, dot01, dot02, dot11, dot12;
float u, v, invDenom;
bool pit(vec2 a, vec2 b, vec2 c, vec2 point)
{
	v0 = c - a;
	v1 = b - a;
	v2 = point - a;
	dot00 = v0.dot(v0);
	dot01 = v0.dot(v1);
	dot02 = v0.dot(v2);
	dot11 = v1.dot(v1);
	dot12 = v1.dot(v2);
	invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
	u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	return (u >= 0) && (v >= 0) && (u + v < 1);
}