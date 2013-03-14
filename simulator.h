#ifndef SIM_H
#define SIM_H

#include "pbody.h"
#include <vector>
#include "renderer.h"
#define RMBB 1
#define RMBNB 3
#define NONE 0
using namespace std;

class simulator
{
	friend class pbody;
	friend class renderer;
private:
	vector<pbody*> bodies;
	vector<pbody*>::iterator it;
	vector<pbody*>::reverse_iterator bap;
	renderer *rend;
	pbody* BodyAtPos(int x, int y);
	int state;
public:
	void process();
	simulator(renderer * r);  
	pbody* BAP;
	pbody* OBAP;
};

#endif //SIM_H