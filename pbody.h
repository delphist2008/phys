#ifndef PBD_H
#define PBD_H
#include "renderer.h"
#include "simulator.h"
#include "helper.h"
#include "vec2d.h"

class pbody
{
	friend class simulator;
	friend class renderer;
	friend class ui;
private:
	int _x, _y;
	int _k;
	HBRUSH pbrush, bbbrush;		
	HBRUSH hlbrush, stbrush;
	HPEN ppen, bbpen;		
	HPEN cpen;
	HBRUSH cbrush;
	vec2 l_countour[3];
	vec2 g_countour[3];
	RECT bbox;
	double angle;
	double ang_vel;
	double mass;
	double I;
	vec2 centre_g;
	vec2 centre_l;
	renderer *re;
	bool ishighlited;
	unsigned long long lastupdated;
	double inangl;
	void process();
	void draw();
	void gcourecalc();
	vec2 vel;
	collision colis;
	bool coll;
	int col_edge;
	bool isstatic;
public:
	pbody(vec2 cnt[3], COLORREF pclr, int cnt_wdth, simulator *sim);
	void addimpulse(vec2 origin, vec2 normal, float impulse);
	void check_coll(pbody * body);
	vec2 vel_temp;
	vec2 pos_temp;
	float angvel_temp;
	float calcI();
};

#endif // PBD_H