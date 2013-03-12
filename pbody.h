#ifndef PBD_H
#define PBD_H
#include "renderer.h"
#include "simulator.h"

class pbody
{
	friend class simulator;
	friend class renderer;
private:
	HBRUSH pbrush;
	HPEN ppen;
	POINT countour[3];
	POINT ang_countour[3];
	renderer *re;
	void draw();
	float angle;
	float ang_vel;
	void angcourecalc();
	POINT centre;
	void process();
public:
	pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim);
	void setAV(float av);
};

#endif // PBD_H