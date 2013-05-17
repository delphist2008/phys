#ifndef PBD_H
#define PBD_H
#include "renderer.h"
#include "simulator.h"
#include "helper.h"



class pbody
{
	friend class simulator;
	friend class renderer;
	friend class ui;
private:
	int _x, _y;
	int _k;
	int _n;
	HBRUSH pbrush, bbbrush;		//standart brush; bounding box brush
	HBRUSH hlbrush;				//on mouse hover brush
	HPEN ppen, bbpen;			//standart pen; bounding box pen
	POINT l_countour[3];
	POINT g_countour[3];
	RECT bbox;
	double angle;
	double ang_vel;
	double ang_accel;
	double impulse_mom;
	double mass;
	double I;
	fpoint centre_g;
	POINT centre_l;
	renderer *re;
	bool ishighlited;
	unsigned long long lastupdated;
	double inangl;
	HRGN pol;
	void process();
	void draw();
	void gcourecalc();
	void setAV(float av);
	fpoint vel;
	double impulse;
	double impulse_moment;
	double a, b, c;
	float v, divis;
fpoint maxvel;
public:
	pbody(POINT cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim);
	void addimpulse(POINT origin, fpoint impulse);
};

#endif // PBD_H