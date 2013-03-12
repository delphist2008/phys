#include "renderer.h"
using namespace std;

void renderer::init(simulator *s)
{
  window = GetConsoleWindow (); 
	screen_dc = GetDC (window);
	buffer_dc = CreateCompatibleDC(screen_dc);
	GetClientRect(window, &screen_dim);
	buffer_bmp = CreateCompatibleBitmap(screen_dc, screen_dim.right, screen_dim.bottom);
	SelectObject(buffer_dc, buffer_bmp);
	SetBkColor (buffer_dc, BGCLR);
	bgbrush = CreateSolidBrush(BGCLR);
	bgpen =  GetStockPen(BLACK_PEN);
	sim = s;
}

void renderer::render()
{
	SelectBrush(buffer_dc, bgbrush);
	SelectPen(buffer_dc, bgpen);
	Rectangle(buffer_dc, 0, 0, screen_dim.right, screen_dim.bottom);
	for (sim->it = sim->bodies.begin(); sim->it < sim->bodies.end(); sim->it++)
		(*sim->it)->draw();
	BitBlt(screen_dc, 0,0, screen_dim.right, screen_dim.bottom, buffer_dc, 0,0, SRCCOPY);
}

void renderer::exit()
{
	SelectBitmap(buffer_dc, NULL);
	SelectBrush(buffer_dc, NULL);
	SelectPen(buffer_dc, NULL);
	DeleteBrush(bgbrush);
	DeletePen(bgpen);
	DeleteBitmap(buffer_bmp);
	ReleaseDC (window, screen_dc); 
}


void renderer::draw_triangle(POINT cnt[3], HBRUSH &brsh, HPEN &pn)
{
	SelectBrush(buffer_dc, brsh);
	SelectPen(buffer_dc, pn);
	Polygon(buffer_dc, cnt, 3);
}
