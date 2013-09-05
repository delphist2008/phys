#ifndef SIM_H
#define SIM_H

#include "pbody.h"
#include <vector>
#include "renderer.h"
#include "ui.h"
#include "helper.h"
#include "vec2d.h"
using namespace std;

class simulator
{
	friend class pbody;
	friend class renderer;
	friend class ui;
private:
	vector<pbody*> bodies;
	vector<pbody*>::iterator it;
	vector<pbody*>::iterator it2;
	vector<pbody*>::reverse_iterator bap;
	renderer *rend;
	ui * UI;
	pbody* BodyAtPos(vec2 p);
	vec2 grav;
	float energy;
public:
	void process();
	void init (renderer * r, ui * u);
	simulator() {};  
};

#endif //SIM_H