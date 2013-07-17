#include "helper.h"


long long  area (POINT a, POINT  b, POINT  c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long  area (int ax, int ay, int bx, int by, int cx, int cy) 
{
	return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

bool intersect_1 (int a, int b, int c, int d) 
{
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}

bool intersect (POINT  a, POINT  b, POINT  c, POINT  d) 
{
	return intersect_1 (a.x, b.x, c.x, d.x)
		&& intersect_1 (a.y, b.y, c.y, d.y)
		&& area(a,b,c) * area(a,b,d) <= 0
		&& area(c,d,a) * area(c,d,b) <= 0;
}


bool intersect (int  ax, int ay,  int  bx, int by, int cx, int cy, int dx, int dy)
{
	return intersect_1 (ax, bx, cx, dx)
		&& intersect_1 (ay, by, cy, dy)
		&& area(ax, ay, bx, by, cx, cy) * area(ax, ay, bx, by,dx, dy) <= 0
		&& area(cx, cy, dx, dy, ax, ay) * area(cx, cy, dx, dy, bx, by) <= 0;
}