#include "pbody.h"

pbody::pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim)
{
	pbrush = CreateSolidBrush(pclr);
	ppen = CreatePen(0, cnt_wdth, 0);
	countour[0] = cnt[0];
	countour[1] = cnt[1];
	countour[2] = cnt[2];

	ang_countour[0] = cnt[0];
	ang_countour[1] = cnt[1];
	ang_countour[2] = cnt[2];

	centre.x = (cnt[0].x+ cnt[1].x+ cnt[2].x)/3;
	centre.y = (cnt[0].y+ cnt[1].y+ cnt[2].y)/3;

	re = sim->rend;
	angle = 0;
	ang_vel = 0;
	sim->bodies.push_back(this);
}


void pbody::draw()
{
	re->draw_triangle(ang_countour, pbrush, ppen);
}


void pbody::process()
{
	angle += ang_vel;
	angcourecalc();
}

void pbody::setAV(float av)
{
	ang_vel = av;
}


int _x, _y;
int _k;
void pbody::angcourecalc()
{
	for (_k = 0; _k < 3; _k++)
	{
	_x = centre.x - countour[_k].x;
	_y = centre.y - countour[_k].y;
	ang_countour[_k].x = _x*cos(angle) - _y*sin(angle) + centre.x;
	ang_countour[_k].y = _x*sin(angle) + _y*cos(angle) + centre.y;
	}
 }