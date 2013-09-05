#include "pbody.h"

pbody::pbody(vec2 cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim)
{
	pbrush = CreateSolidBrush(pclr);
	hlbrush = CreateSolidBrush(RGB(0,200,0));
	stbrush = CreateHatchBrush(4,RGB(0,0,0));
	cbrush = CreateSolidBrush(RGB(0,0,255));
	ppen = CreatePen(0, cnt_wdth, 0);
	cpen = CreatePen(0, cnt_wdth, RGB(0,255,0));
	centre_g = (cnt[0]+ cnt[1]+ cnt[2])/3.0;
	l_countour[1] = cnt[1];
	l_countour[2] = cnt[2];
	l_countour[0] = vec2(0,0);
	l_countour[1] = l_countour[1] - cnt[0];
	l_countour[2] = l_countour[2] - cnt[0];
	if ((l_countour[1].x  -  l_countour[0].x )* (l_countour[2].y  -  l_countour[1].y ) - (l_countour[2].x  -  l_countour[1].x ) * (l_countour[1].y  -  l_countour[0].y ) >= 0) std::reverse(&(l_countour[0]), &(l_countour[2]));
	centre_l = (l_countour[0]+ l_countour[1]+ l_countour[2])/3.0;
	gcourecalc();
	re = sim->rend;
	angle = 0;
	ang_vel = 0;
	bbbrush = GetStockBrush(HOLLOW_BRUSH);
	bbpen = CreatePen(2, 1, RGB(0,0,0));
	ishighlited = false;
	lastupdated = GetTickCount();
	mass = (abs(((l_countour[2].x-l_countour[1].x)/100.0)*((l_countour[1].y-l_countour[0].y)/100.0)-((l_countour[1].x-l_countour[0].x)/100.0)*((l_countour[2].y-l_countour[1].y)/100.0)))/2.0;
	I = calcI();
	sim->bodies.push_back(this);
	vel = vec2(0,0);
	col_edge = 0;
	coll = false;
	if (re->UI->state == STATIC) isstatic = true; 
	else
		isstatic = false;
	angvel_temp = 0;
	vel_temp=vec2(0,0);
	pos_temp=vec2(0,0);
	

}

void pbody::draw()  // todo: move all drawing stuff into rendererer
{
	re->draw_triangle(g_countour, coll ? & cbrush : isstatic ? &stbrush : (ishighlited ? &hlbrush : &pbrush), &ppen, &cpen, col_edge);
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

vec2 pt;
float rad;
double dmass;
float pbody::calcI()
{
	float res = 0;
	dmass = mass / ((abs(((l_countour[2].x-l_countour[1].x))*((l_countour[1].y-l_countour[0].y))-((l_countour[1].x-l_countour[0].x))*((l_countour[2].y-l_countour[1].y))))/2.0);
	for (pt.x = bbox.left; pt.x < bbox.right; pt.x++)
	{
		for (pt.y = bbox.top; pt.y < bbox.bottom; pt.y++)
			if (pit(g_countour[0], g_countour[1], g_countour[2], pt ))
			{
				rad = (pt-centre_g).length();
				res += (dmass) *  rad * rad;
			}
	}
	return res;
}


double tk;
void pbody::process()
{
	centre_g += pos_temp;
	vel += vel_temp;
	ang_vel += angvel_temp;
	tk = 0.0005;//((GetTickCount() - lastupdated)/10000.0);
	lastupdated = GetTickCount();
	angle += ang_vel*tk;
	centre_g+= vel*tk;
	gcourecalc();
	angvel_temp = 0;
	vel_temp=vec2(0,0);
	pos_temp=vec2(0,0);
}

void pbody::gcourecalc()
{
	for (_k = 0; _k < 3; _k++)
	{
		_x =  l_countour[_k].x - centre_l.x ;
		_y =  l_countour[_k].y - centre_l.y;
		g_countour[_k].x = float(_x*cos(angle) - _y*sin(angle) + centre_g.x);
		g_countour[_k].y = float(_x*sin(angle) + _y*cos(angle) + centre_g.y);
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
}

vec2 RA, R1, R2; 
void pbody::addimpulse(vec2 origin, vec2 normal, float impulse)
{
	if (!isstatic)
	{
		RA  = origin - centre_g;
		vel_temp += normal *impulse /mass;
		angvel_temp += (impulse * (normal.y * RA.x - normal.x * RA.y) /I);
	}
}

int vcount;
vec2 vcoor;
float D;
vec2 _c1, _c2;
float vab;
float Z1, Z2;
float J;
float impulse;
bool co;
pbody *m1, *m2;
int vc;
void pbody::check_coll(pbody * body)
{
	m1 = this;
	m2 = body;

	for (vcount = 0; vcount < 3; vcount++)
	{
		co = false;
		vcoor = this->g_countour[vcount];
		if (vcoor.x < (body->bbox.left) ||  vcoor.x > (body->bbox.right) ||   vcoor.y < (body->bbox.top)  || vcoor.y > (body->bbox.bottom))
			continue;
		if (pit(body->g_countour[0],body->g_countour[1], body->g_countour[2],vcoor))
		{
			colis.position = vcoor;
			for (vc = 0; vc < 3; vc++)
			{
				if (intersect(centre_g.x, centre_g.y, vcoor.x, vcoor.y, body->g_countour[vc].x, body->g_countour[vc].y, body->g_countour[(vc+1)%3].x, body->g_countour[(vc+1)%3].y))
				{
					colis.vector.y = -1.0*(body->g_countour[vc].x -body->g_countour[(vc+1)%3].x);
					colis.vector.x = (body->g_countour[vc].y -body->g_countour[(vc+1)%3].y);
					_c1 = body->g_countour[vc];
					_c2 = body->g_countour[(vc+1)%3];
					co = true;
				}
			}
			if (co)
			{
				colis.vector /= colis.vector.length();
				D = abs(((_c1.y-_c2.y)*vcoor.x +(_c2.x-_c1.x)*vcoor.y + (_c1.x*_c2.y - _c2.x*_c1.y))/sqrt((_c2.x-_c1.x)*(_c2.x-_c1.x) + (_c2.y-_c1.y)*(_c2.y-_c1.y)));
				colis.vector *= D;

				R1 = colis.position - m1->centre_g;
				R2 = colis.position - m2->centre_g;

				vab =  colis.vector.x * (m1->vel.x - m1->ang_vel * R1.y - m2->vel.x + m2->ang_vel * R2.y) + 
					colis.vector.y * (m1->vel.y + m1->ang_vel * R1.x - m2->vel.y - m2->ang_vel * R2.x);

				Z1 = (colis.vector.y * R1.x - colis.vector.x * R1.y) /m1->I;
				Z2 = (colis.vector.y * R2.x - colis.vector.x * R2.y) /m2->I;

				J = colis.vector.x *  (colis.vector.x / m1->mass - R1.y * Z1 + colis.vector.x / m2->mass + R2.y * Z2) 
					+ colis.vector.y * (colis.vector.y / m1->mass + R1.x * Z1 / m1->I + colis.vector.y / m2->mass - R2.x * Z2 / m2->I);

				impulse = ((-(1.0 - 0.3) * vab) / J)/2.0;

				if (impulse >= 0)
				{
					m2->addimpulse(colis.position, colis.vector, -impulse);
					m1->addimpulse(colis.position, colis.vector, impulse);
				}
				if (!body->isstatic)
					body->pos_temp -= colis.vector;
				if (!isstatic)
					pos_temp += colis.vector;
			}
		}
	}
}