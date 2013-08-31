#include "pbody.h"


pbody::pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim)
{
	pbrush = CreateSolidBrush(pclr);
	hlbrush = CreateSolidBrush(RGB(0,200,0));
	cbrush = CreateSolidBrush(RGB(0,0,255));
	ppen = CreatePen(0, cnt_wdth, 0);
	cpen = CreatePen(0, cnt_wdth, RGB(0,255,0));
	centre_g.x = (cnt[0].x+ cnt[1].x+ cnt[2].x)/3;
	centre_g.y = (cnt[0].y+ cnt[1].y+ cnt[2].y)/3;
	l_countour[1] = cnt[1];
	l_countour[2] = cnt[2];
	l_countour[0].x = l_countour[0].y = 0;
	l_countour[1].x -= cnt[0].x;
	l_countour[1].y -= cnt[0].y;
	l_countour[2].x -= cnt[0].x;
	l_countour[2].y -= cnt[0].y;
	sim->UI->vect = (l_countour[1].x  -  l_countour[0].x )* (l_countour[2].y  -  l_countour[1].y ) - (l_countour[2].x  -  l_countour[1].x ) * (l_countour[1].y  -  l_countour[0].y );
	if (sim->UI->vect >= 0) std::reverse(&(l_countour[0]), &(l_countour[2]));
	centre_l.x = (l_countour[0].x+ l_countour[1].x+ l_countour[2].x)/3;
	centre_l.y = (l_countour[0].y+ l_countour[1].y+ l_countour[2].y)/3;
	gcourecalc();
	re = sim->rend;
	angle = 0;
	ang_vel = 0;
	bbbrush = GetStockBrush(HOLLOW_BRUSH);
	bbpen = CreatePen(2, 1, RGB(0,0,0));
	ishighlited = false;
	lastupdated = GetTickCount();
	mass = abs( ((l_countour[2].x-l_countour[1].x)*(l_countour[1].y-l_countour[0].y)-(l_countour[1].x-l_countour[0].x)*(l_countour[2].y-l_countour[1].y)) / 160.0);
	a = sqrt(pow((l_countour[0].x - l_countour[1].x),2) + pow((l_countour[0].y - l_countour[1].y),2));
	b = sqrt(pow((l_countour[1].x - l_countour[2].x),2) + pow((l_countour[1].y - l_countour[2].y),2));
	c = sqrt(pow((l_countour[2].x - l_countour[0].x),2) + pow((l_countour[2].y - l_countour[0].y),2));
	I = double((mass * ((b*b + ((b*b - a*a -c*c)/(2*a)) + pow(((b*b - a*a -c*c)/(2*a)), 2) + sqrt(b*b - pow(((b*b - a*a -c*c)/(2*a)), 2) ))))/156000);
	ang_accel = 0;
	sim->bodies.push_back(this);
	vel.x = 0;
	vel.y = 0;
	col_edge = 0;
	coll = false;
	}

void pbody::draw()
{
	re->draw_triangle(g_countour, coll ? & cbrush : (ishighlited ? &hlbrush : &pbrush), &ppen, &cpen, col_edge);
	if (coll)
	{
		MoveToEx(re->buffer_dc, colis.position.x, colis.position.y, NULL);
		LineTo(re->buffer_dc, colis.position.x+colis.vector.x, colis.position.y+colis.vector.y);
	}
	if (DRAWBOUNDING)
	{
		SelectBrush(re->buffer_dc, bbbrush);
		SelectPen(re->buffer_dc, bbpen);
		Rectangle(re->buffer_dc, bbox.left, bbox.top, bbox.right, bbox.bottom);
		SetPixel(re->buffer_dc, centre_g.x, centre_g.y, 0);
		SetPixel(re->buffer_dc, centre_g.x+1, centre_g.y, 0);
		SetPixel(re->buffer_dc, centre_g.x-1, centre_g.y, 0);
		SetPixel(re->buffer_dc, centre_g.x, centre_g.y+1, 0);
		SetPixel(re->buffer_dc, centre_g.x, centre_g.y-1, 0);
	}
}

void pbody::process()
{
	if (bbox.bottom >= re->screen_dim.bottom || bbox.top <= re->screen_dim.top ) vel.y *= -1.0; 
	if (bbox.right >= re->screen_dim.right || bbox.left <= re->screen_dim.left ) vel.x *= -1.0; 
	angle += ang_vel*((GetTickCount() - lastupdated)/1000.0);
	centre_g.x += vel.x;
	centre_g.y += vel.y;
	lastupdated = GetTickCount();
	gcourecalc();
	impulse = sqrt(vel.x*vel.x + vel.y*vel.y) * mass;
	impulse_moment = ang_vel * I;
	
}

void pbody::setAV(float av)
{
	ang_vel = av;
}

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


void pbody::addimpulse(POINT origin, fpoint impulse)
{
	impulse_mom = (((origin.x - centre_g.x) / 100.0)*impulse.y - ((origin.y - centre_g.y)/100.0)*impulse.x);
	ang_accel = -impulse_mom / I;
	ang_vel += ang_accel;
	v = sqrt(impulse.x*impulse.x + impulse.y*impulse.y)/mass;
	divis = sqrt(impulse.x*impulse.x + impulse.y*impulse.y) / v;
	maxvel.x = impulse.x / divis;
	maxvel.y = impulse.y / divis;
	v = (mass*(sqrt(maxvel.x*maxvel.x + maxvel.y*maxvel.y)) - I * abs(ang_accel)/mass);
	vel.x -= impulse.x / v;
	vel.y -= impulse.y / v;
}

int vcount;
int x, y;
float len;
float D;
float _cx1, _cx2, _cy1, _cy2;

void pbody::check_coll(pbody * body)
{
	for (vcount = 0; vcount < 3; vcount++)
	{
		x = this->g_countour[vcount].x;
		y = this->g_countour[vcount].y;
		if (x < (body->bbox.left) ||  x > (body->bbox.right) ||   y < (body->bbox.top)  || y > (body->bbox.bottom))
			continue;
		if (PtInRegion((body)->pol, x,y))
		{
			//body->coll = true;
			coll = true;
			colis.position.x = x;
			colis.position.y = y;
			if (intersect(centre_g.x, centre_g.y, x, y, body->g_countour[0].x, body->g_countour[0].y, body->g_countour[1].x, body->g_countour[1].y))
			{
				body->col_edge = 1;
				colis.vector.y = -1.0*(body->g_countour[0].x -body->g_countour[1].x);
				colis.vector.x = (body->g_countour[0].y -body->g_countour[1].y);

				_cx1 = body->g_countour[0].x;
				_cx2 = body->g_countour[1].x;

				_cy1 = body->g_countour[0].y;
				_cy2 = body->g_countour[1].y;
				
			}
			else if
				(intersect(centre_g.x, centre_g.y, x, y, body->g_countour[1].x, body->g_countour[1].y, body->g_countour[2].x, body->g_countour[2].y))
			{
				body->col_edge = 2;
				colis.vector.y = -1.0*(body->g_countour[1].x -body->g_countour[2].x);
				colis.vector.x = (body->g_countour[1].y -body->g_countour[2].y);

				_cx1 = body->g_countour[1].x;
				_cx2 = body->g_countour[2].x;

				_cy1 = body->g_countour[1].y;
				_cy2 = body->g_countour[2].y;
			}
			else  if
				(intersect(centre_g.x, centre_g.y, x, y, body->g_countour[2].x, body->g_countour[2].y, body->g_countour[0].x, body->g_countour[0].y))
			{
				body->col_edge = 3;
				colis.vector.y = -1.0*(body->g_countour[2].x -body->g_countour[0].x);
				colis.vector.x = (body->g_countour[2].y -body->g_countour[0].y);

				_cx1 = body->g_countour[2].x;
				_cx2 = body->g_countour[0].x;

				_cy1 = body->g_countour[2].y;
				_cy2 = body->g_countour[0].y;
			}
			len = sqrt(colis.vector.x*colis.vector.x+colis.vector.y*colis.vector.y);
			colis.vector.y /= len;
			colis.vector.x /= len;
			D = -((_cy1-_cy2)*x +(_cx2-_cx1)*y + (_cx1*_cy2 - _cx2*_cy1))/sqrt((_cx2-_cx1)*(_cx2-_cx1) + (_cy2-_cy1)*(_cy2-_cy1));
			colis.vector.x *= D/2.0;
			colis.vector.y *= D/2.0;

			body->centre_g.x -= colis.vector.x;
			body->centre_g.y -= colis.vector.y;
			centre_g.x -= colis.vector.x;
			centre_g.y -= colis.vector.y;
			
			colis.vector.x *= mass;
			colis.vector.y *= mass;
			body->addimpulse(colis.position, colis.vector);
			colis.vector.x *= -1.0;
			colis.vector.y *= -1.0;
			addimpulse(colis.position, colis.vector);
			break;

		}
	}
}