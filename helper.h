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

bool intersect (fpoint  a, fpoint  b, fpoint  c, fpoint  d) ;
bool intersect (float  ax, float ay,  float  bx, float by, float cx, float cy, float dx, float dy);

struct collision
{
	fpoint position;
	fpoint vector;
};


#endif //HELP_H
