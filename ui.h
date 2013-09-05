#ifndef UI_H
#define UI_H

#include "renderer.h"
#include "simulator.h"
#include "pbody.h"
#include "helper.h"
#include "vec2d.h"

#define RMBB	0
#define CREATE	1
#define RMBNB	2
#define SELECT	3
#define MOVE	4
#define STATIC	5

static char statelist[10][255] = {"RMBB\0","CREATE\0", "RMBNB\0", "SELECT\0", "MOVE\0", "STATIC\0"};

class ui
{
	friend class pbody;
	friend class simulator;
	friend class renderer;
private:
	void onLMBD();
	void onLMBU();
	void onRMBD();
	void onRMBU();
	void onMM();
	void onKeyDown(int key);
	void onKeyUp(int key);
public:
	void init(simulator * s, renderer * r);
	simulator * sim;
	renderer * rend;
	ui();
	pbody* body_at_click;
	pbody* body_at_cursor;
	pbody* newbody;
	vec2 pol_to_create[3];
	vec2 click_pos;
	vec2 mouse_pos;
	vec2 impulse_apply_vector;
	vec2 impulse_line_begin;
	int click_count;
	int _X, _Y;
	void update();
	int state;
	char debugstr[255];
	int oldstate;
	int dx, dy;
	float fps;
	float fpstmp;
};

#endif //UI_H