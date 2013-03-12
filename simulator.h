#ifndef SIM_H
#define SIM_H

#include "pbody.h"
#include <vector>
#include "renderer.h"
using namespace std;

class simulator
{
	friend class pbody;
	friend class renderer;
private:
	vector<pbody*> bodies;
	vector<pbody*>::iterator it;
	renderer *rend;

public:
	void process();
	simulator(renderer * r);  
};

#endif //SIM_H