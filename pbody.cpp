#include "pbody.h"

pbody::pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim)
{
	pbrush = CreateSolidBrush(pclr);
	ppen = CreatePen(0, cnt_wdth, 0);
	centre_g.x = (cnt[0].x+ cnt[1].x+ cnt[2].x)/3;
	centre_g.y = (cnt[0].y+ cnt[1].y+ cnt[2].y)/3;
	countour[1] = cnt[1];
	countour[2] = cnt[2];
	countour[0].x = countour[0].y = 0;
	countour[1].x -= cnt[0].x;
	countour[1].y -= cnt[0].y;
	countour[2].x -= cnt[0].x;
	countour[2].y -= cnt[0].y;
	centre_l.x = (countour[0].x+ countour[1].x+ countour[2].x)/3;
	centre_l.y = (countour[0].y+ countour[1].y+ countour[2].y)/3;
	angcourecalc();
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
		_x =  countour[_k].x - centre_l.x ;
		_y =  countour[_k].y - centre_l.y;
		ang_countour[_k].x = long(_x*cos(angle) - _y*sin(angle) + centre_g.x);
		ang_countour[_k].y = long(_x*sin(angle) + _y*cos(angle) + centre_g.y);
	}
}