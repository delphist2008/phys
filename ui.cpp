#include "ui.h"


void ui::init(simulator * s, renderer * r)
{
	sim = s;
	rend = r;
}

ui::ui()
{
	click_count = 0;
}

void ui::onLMBD()
{
	pol_to_create[click_count] = click_pos;
	click_count++;
	if (click_count == 3)
	{
		click_count = 0;
		newbody = new pbody(pol_to_create, RGB(255, 10, 0), 3, sim);
	}
}

void ui::onLMBU()
{

}

void ui::onRMBD()
{
	if (body_at_cursor )
	{
		body_at_click = sim->BodyAtPos(mouse_pos.x, mouse_pos.y);
		state = RMBB;
		body_at_click->inangl = body_at_click->angle;
	}
	else state = RMBNB;
}

void ui::onRMBU()
{
	if (state ==  RMBB) 
	{
		force_apply_vector.x = mouse_pos.x - force_line_begin.x;
		force_apply_vector.y = mouse_pos.y - force_line_begin.y;
		body_at_click->addforce(force_line_begin, force_apply_vector);
		state = NONE;
	}
}

void ui::onMM()
{


}

void ui::update()
{
	if (state == RMBB)
	{	
		_X = (click_pos.x - body_at_click->centre_g.x);
		_Y = (click_pos.y - body_at_click->centre_g.y);
		force_line_begin.x = _X*cos(body_at_click->angle - body_at_click->inangl) - _Y*sin(body_at_click->angle - body_at_click->inangl) + body_at_click->centre_g.x;
		force_line_begin.y = _X*sin(body_at_click->angle - body_at_click->inangl) + _Y*cos(body_at_click->angle - body_at_click->inangl) + body_at_click->centre_g.y;
	}
}