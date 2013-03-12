#include "simulator.h"

simulator::simulator(renderer * r)
{
	rend = r;
}

void simulator::process()
{
	for (it = bodies.begin(); it < bodies.end(); it++)
		(*it)->process();
}