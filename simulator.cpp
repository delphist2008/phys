#include "simulator.h"

void simulator::init (renderer * r, ui * u)
{
	rend = r;
	UI = u;
	grav = vec2(0,1);
}

void simulator::process()
{
	energy = 0;
	for (it = bodies.begin(); it < bodies.end(); ++it)
	{
		(*it)->coll = false;
		(*it)->col_edge = 0;
		(*it)->addimpulse((*it)->centre_g, grav, (*it)->mass*10);
	}
	for (it = bodies.begin(); it < bodies.end(); ++it)
	{
		(*it)->ishighlited = false;
		for (it2 = bodies.begin(); it2 < bodies.end(); ++it2)
			if (it != it2)
				(*it)->check_coll(*it2);
	}
	for (it = bodies.begin(); it < bodies.end(); ++it)
	{
		(*it)->process();
		energy += (*it)->vel.length()*(*it)->vel.length() * (*it)->mass;
		energy += (*it)->ang_vel*(*it)->ang_vel * (*it)->I;
	}
	UI->body_at_cursor = BodyAtPos(UI->mouse_pos);
}

pbody* simulator::BodyAtPos(vec2 p)
{
	for (bap = bodies.rbegin(); bap < bodies.rend(); ++bap)
	{
		if (p.x < ((*bap)->bbox.left) ||  p.x > ((*bap)->bbox.right) ||  p.y < ((*bap)->bbox.top)  || p.y > ((*bap)->bbox.bottom))
			continue;
		if (pit((*bap)->g_countour[0], (*bap)->g_countour[1], (*bap)->g_countour[2], p))
		{
			(*bap)->ishighlited = true;
			return (*bap);
		}
	}
	return NULL;
}