#ifndef PBD_H
#define PBD_H
#include "renderer.h"
#include "simulator.h"


class pbody
{
	friend class simulator;
	friend class renderer;
private:
	
	HBRUSH pbrush, bbbrush;
	HBRUSH hlbrush;
	HPEN ppen, bbpen;
	POINT l_countour[3];
	POINT g_countour[3];
	RECT bbox;
	float angle;
	float ang_vel;
	POINT centre_g;
	POINT centre_l;
	renderer *re;
	void process();
	void draw();
	void gcourecalc();
	bool ishighlited;
public:
	pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim);
	void setAV(float av);
	HRGN pol;
};

#endif // PBD_H