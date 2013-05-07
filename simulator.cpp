#include "simulator.h"

void simulator::init (renderer * r, ui * u)
{
	rend = r;
	UI = u;

}

void simulator::process()
{
	for (it = bodies.begin(); it < bodies.end(); it++)
	{
		(*it)->process();
		(*it)->ishighlited = false;
	}
	UI->body_at_cursor = BodyAtPos(UI->mouse_pos.x, UI->mouse_pos.y);
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
















vector<POINT> simulator::penetration(vector<pbody*>::iterator b1, vector<pbody*>::iterator b2)
{
	vector <POINT> result;
	return result;
	
}