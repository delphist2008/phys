#ifndef REND_H
#define REND_H

#include <windows.h>   
#include <windowsx.h>  
#include "simulator.h"

#define BGCLR RGB(128, 128, 255)

class renderer
{
	friend class simulator;
	friend class pbody;
private:
	HWND window;
	HDC screen_dc, buffer_dc;
	RECT screen_dim;
	HBITMAP buffer_bmp;
	HBRUSH bgbrush;
	HPEN bgpen;
	simulator *sim;
	
public:
	void init(simulator *s);
	void render();
	void exit();
	void draw_triangle(POINT cnt[3], HBRUSH &brsh, HPEN &pn);
};

#endif //REND_H