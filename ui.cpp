#include "ui.h"

void ui::init(simulator * s, renderer * r)
{
	sim = s;
	rend = r;
	state = CREATE;
	fpstmp = 0;
	fps = 0;
}

ui::ui()
{
	click_count = 0; 
}

void ui::onLMBD()
{
	if (state == SELECT)
	{
		if (body_at_cursor )
		{
			body_at_click = sim->BodyAtPos(mouse_pos);
			state = MOVE;
			dx = mouse_pos.x - body_at_click->centre_g.x;
			dy = mouse_pos.y - body_at_click->centre_g.y;
		}
	}
	else
		if (state == MOVE) 
			state = SELECT;
	if (state == CREATE || state == STATIC)
	{
		pol_to_create[click_count] = click_pos;
		click_count++;
		if (click_count == 3)
		{
			click_count = 0;
			newbody = new pbody(pol_to_create, RGB(255, 10, 0), 3, sim);
		}
	}
}

void ui::onLMBU()
{
	if (state == MOVE) state = SELECT;
}

void ui::onRMBD()
{
	if (body_at_cursor )
	{
		body_at_click = sim->BodyAtPos(mouse_pos);
		oldstate = state;
		state = RMBB;
		body_at_click->inangl = body_at_click->angle;
	}
}
float im;
void ui::onRMBU()
{
	if (state ==  RMBB) 
	{

		impulse_apply_vector.x = -mouse_pos.x + impulse_line_begin.x;
		impulse_apply_vector.y = -mouse_pos.y + impulse_line_begin.y;
		im = sqrt(impulse_apply_vector.x * impulse_apply_vector.x + impulse_apply_vector.y*impulse_apply_vector.y );
		impulse_apply_vector.x /= im;
		impulse_apply_vector.y /= im;
		body_at_click->addimpulse(impulse_line_begin, impulse_apply_vector, im);
		state = oldstate;
	}
}

void ui::onMM()
{
	if (state == MOVE)
	{
		body_at_click->centre_g.x = mouse_pos.x -dx;
		body_at_click->centre_g.y = mouse_pos.y -dy;
	}

}

int u, o;
vec2 cen;
void ui::onKeyDown(int key)
{
	if (key == 77 ) //m
		if (state == SELECT)	
			state = CREATE;
		else state = SELECT;
		if (key == 67 ) //c
		{
			state = CREATE;
			sim->bodies.clear();
		}
		if (key == 83)//s
		{
			if (state != STATIC)
			{
				oldstate = state;
				state = STATIC;
			}
			else state = oldstate;
		}
		if (key == 81 ) //q
		{
			for (u = 0; u < 50; u++)
			{
				cen.x = rand()%rend->screen_dim.right;
				cen.y = rand()%rend->screen_dim.bottom;
				for (o=0; o < 3; o++)
				{
					pol_to_create[o].x = cen.x +rand()%70 - rand()%70;
					pol_to_create[o].y = cen.y +rand()%70 - rand()%70;
				}
				newbody = new pbody(pol_to_create, RGB(255, 10, 0), 3, sim);
			}
		}
}


void ui::onKeyUp(int key)
{

}

void ui::update()
{
	if (state == RMBB)
	{	
		_X = (click_pos.x - body_at_click->centre_g.x);
		_Y = (click_pos.y - body_at_click->centre_g.y);
		impulse_line_begin.x = _X*cos(body_at_click->angle - body_at_click->inangl) - _Y*sin(body_at_click->angle - body_at_click->inangl) + body_at_click->centre_g.x;
		impulse_line_begin.y = _X*sin(body_at_click->angle - body_at_click->inangl) + _Y*cos(body_at_click->angle - body_at_click->inangl) + body_at_click->centre_g.y;
	}
	sprintf(debugstr, "state= %s x= %f y= %f fps=%f, energy = %f\0", statelist[state], mouse_pos.x, mouse_pos.y, fps, sim->energy/10000.0);
}