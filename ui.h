#ifndef UI_H
#define UI_H

#include "renderer.h"
#include "simulator.h"
#include "pbody.h"

#define RMBB 1
#define RMBNB 3
#define NONE 0

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
public:
	void init(simulator * s, renderer * r);
	simulator * sim;
	renderer * rend;
	ui();
	pbody* body_at_click;
	pbody* body_at_cursor;
	pbody* newbody;
	POINT pol_to_create[3];
	POINT click_pos;
	POINT mouse_pos;
	POINT force_line_begin;
	POINT force_apply_vector;
	int click_count;
	int _X, _Y;
	void update();
	int state;
};


#endif //UI_H







