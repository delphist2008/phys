#ifndef SIM_H
#define SIM_H

#include "pbody.h"
#include <vector>
#include "renderer.h"
#include "ui.h"
#include "helper.h"
using namespace std;





class simulator
{
	friend class pbody;
	friend class renderer;
	friend class ui;
private:
	vector<pbody*> bodies;
	vector<pbody*>::iterator it;
	vector<pbody*>::reverse_iterator bap;
	renderer *rend;
	ui * UI;
	pbody* BodyAtPos(int x, int y);
	vector<POINT> penetration(vector<pbody*>::iterator b1, vector<pbody*>::iterator b2);
public:
	void process();
	void init (renderer * r, ui * u);
	simulator() {};  
};

#endif //SIM_H