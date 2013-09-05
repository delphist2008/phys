#ifndef HELP_H
#define HELP_H

#include <utility>
using namespace std;
#include <windows.h>   
#include <windowsx.h>
#include "vec2d.h"

bool intersect (vec2  a, vec2  b, vec2  c, vec2  d) ;
bool intersect (float  ax, float ay,  float  bx, float by, float cx, float cy, float dx, float dy);
bool pit(vec2 a, vec2 b, vec2 c, vec2 point);

struct collision
{
	vec2 position;
	vec2 vector;
};

#endif //HELP_H
