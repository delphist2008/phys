#ifndef PBD_H
#define PBD_H
#include "renderer.h"
#include "simulator.h"


class pbody
{
	friend class simulator;
	friend class renderer;
private:
	HBRUSH pbrush, bbbrush;		//standart brush; bounding box brush
	HBRUSH hlbrush;				//on mouse hover brush
	HPEN ppen, bbpen;			//standart pen; bounding box pen
	POINT l_countour[3];
	POINT g_countour[3];
	RECT bbox;
	double angle;
	double ang_vel;
	double ang_accel;
	double force_mom;
	double mass;
	double I;
	POINT centre_g;
	POINT centre_l;
	renderer *re;
	void process();
	void draw();
	void gcourecalc();
	bool ishighlited;
	unsigned long long lastupdated;
	double inangl;
public:
	pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim);
	void setAV(float av);
	HRGN pol;
	void addforce(POINT origin, POINT force);
};

#endif // PBD_H