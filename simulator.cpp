#include "simulator.h"

simulator::simulator(renderer * r)
{
	rend = r;
	state = NONE;
}

int _X, _Y;
void simulator::process()
{
	for (it = bodies.begin(); it < bodies.end(); it++)
	{
		(*it)->process();
		(*it)->ishighlited = false;
	}
	BAP = BodyAtPos(rend->mouse.x, rend->mouse.y);
	if (state == RMBB)
	{	_X = (rend->omouse.x - OBAP->centre_g.x);
		_Y = (rend->omouse.y - OBAP->centre_g.y);
		rend->lmouse.x = _X*cos(OBAP->angle - OBAP->inangl) - _Y*sin(OBAP->angle - OBAP->inangl) + OBAP->centre_g.x;
		rend->lmouse.y = _X*sin(OBAP->angle - OBAP->inangl) + _Y*cos(OBAP->angle - OBAP->inangl) + OBAP->centre_g.y;
	}
}

pbody* simulator::BodyAtPos(int x, int y)
{
	for (bap = bodies.rbegin(); bap < bodies.rend(); bap++)
	{
		if (x < ((*bap)->bbox.left) ||  x > ((*bap)->bbox.right) ||   y < ((*bap)->bbox.top)  || y > ((*bap)->bbox.bottom))
			continue;
		if (PtInRegion((*bap)->pol, x,y))
		{
			(*bap)->ishighlited = true;
			return (*bap);
		}
	}
	return NULL;
}