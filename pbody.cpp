#include "pbody.h"

pbody::pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim)
{
	pbrush = CreateSolidBrush(pclr);
	hlbrush = CreateSolidBrush(RGB(0,200,0));
	ppen = CreatePen(0, cnt_wdth, 0);
	centre_g.x = (cnt[0].x+ cnt[1].x+ cnt[2].x)/3;
	centre_g.y = (cnt[0].y+ cnt[1].y+ cnt[2].y)/3;
	l_countour[1] = cnt[1];
	l_countour[2] = cnt[2];
	l_countour[0].x = l_countour[0].y = 0;
	l_countour[1].x -= cnt[0].x;
	l_countour[1].y -= cnt[0].y;
	l_countour[2].x -= cnt[0].x;
	l_countour[2].y -= cnt[0].y;
	centre_l.x = (l_countour[0].x+ l_countour[1].x+ l_countour[2].x)/3;
	centre_l.y = (l_countour[0].y+ l_countour[1].y+ l_countour[2].y)/3;
	gcourecalc();
	re = sim->rend;
	angle = 0;
	ang_vel = 0;
	bbbrush = GetStockBrush(HOLLOW_BRUSH);
	bbpen = CreatePen(2, 1, RGB(0,0,0));
	ishighlited = false;
	sim->bodies.push_back(this);
}


void pbody::draw()
{
	re->draw_triangle(g_countour, ishighlited ? &hlbrush : &pbrush, &ppen);
	SelectBrush(re->buffer_dc, bbbrush);
	SelectPen(re->buffer_dc, bbpen);
	Rectangle(re->buffer_dc, bbox.left, bbox.top, bbox.right, bbox.bottom);
	SetPixel(re->buffer_dc, centre_g.x, centre_g.y, 0);
	SetPixel(re->buffer_dc, centre_g.x+1, centre_g.y, 0);
	SetPixel(re->buffer_dc, centre_g.x-1, centre_g.y, 0);
	SetPixel(re->buffer_dc, centre_g.x, centre_g.y+1, 0);
	SetPixel(re->buffer_dc, centre_g.x, centre_g.y-1, 0);
}


void pbody::process()
{
	angle += ang_vel;
	gcourecalc();
}

void pbody::setAV(float av)
{
	ang_vel = av;
}


int _x, _y;
int _k;
void pbody::gcourecalc()
{
	for (_k = 0; _k < 3; _k++)
	{
		_x =  l_countour[_k].x - centre_l.x ;
		_y =  l_countour[_k].y - centre_l.y;
		g_countour[_k].x = long(_x*cos(angle) - _y*sin(angle) + centre_g.x);
		g_countour[_k].y = long(_x*sin(angle) + _y*cos(angle) + centre_g.y);
	}
	bbox.left = bbox.right =  g_countour[0].x;
	bbox.top = bbox.bottom =  g_countour[0].y;
	for (_k = 1; _k < 3; _k++)
	{
		if (g_countour[_k].x <  bbox.left ) bbox.left = g_countour[_k].x;
		if (g_countour[_k].x >  bbox.right ) bbox.right = g_countour[_k].x;
		if (g_countour[_k].y <  bbox.top ) bbox.top = g_countour[_k].y;
		if (g_countour[_k].y >  bbox.bottom ) bbox.bottom = g_countour[_k].y;
	}
	DeleteObject(pol);
	pol = CreatePolygonRgn(g_countour, 3, WINDING);
}

