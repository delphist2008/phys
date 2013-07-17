#ifndef HELP_H
#define HELP_H

#include <utility>
using namespace std;
#include <windows.h>   
#include <windowsx.h>

struct fpoint
{
	float x, y;
};

bool intersect (POINT  a, POINT  b, POINT  c, POINT  d) ;
bool intersect (int  ax, int ay,  int  bx, int by, int cx, int cy, int dx, int dy);

struct collision
{
	POINT position;
	fpoint vector;
};


#endif //HELP_H
