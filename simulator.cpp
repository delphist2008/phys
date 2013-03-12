#include "simulator.h"

simulator::simulator(renderer * r)
{
	rend = r;
}

void simulator::process()
{
	for (it = bodies.begin(); it < bodies.end(); it++)
	{
		(*it)->process();
		(*it)->ishighlited = false;
	}
	BAP = BodyAtPos(rend->mouse.x, rend->mouse.y);
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