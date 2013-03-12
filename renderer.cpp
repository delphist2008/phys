#include "renderer.h"
using namespace std;


void renderer::init(simulator *s)
{
	screen = new CClientDC(FromHandle(m_hWnd));
	buffer = new CMemDC(screen);
	screen_dc = screen->GetHDC();
	buffer_dc = buffer->GetHDC();
	screen_dim = GetClientRect();
	buffer_bmp.CreateCompatibleBitmap(screen, screen_dim.right, screen_dim.bottom);
	buffer->SelectObject(&buffer_bmp);
	buffer->SetBkColor(BGCLR);
	bgbrush = CreateSolidBrush(BGCLR);
	bgpen =  GetStockPen(BLACK_PEN);
	sim = s;
}

void renderer::draw_triangle(POINT cnt[3], HBRUSH &brsh, HPEN &pn)
{
	SelectBrush(buffer_dc, brsh);
	SelectPen(buffer_dc, pn);
	Polygon(buffer_dc, cnt, 3);
}

void renderer::Draw()
{
	SelectBrush(buffer_dc, bgbrush);
	SelectPen(buffer_dc, bgpen);
	Rectangle(buffer_dc, 0, 0, screen_dim.right, screen_dim.bottom);
	for (sim->it = sim->bodies.begin(); sim->it < sim->bodies.end(); sim->it++)
			(*sim->it)->draw();
	BitBlt(screen_dc, 0,0, screen_dim.right, screen_dim.bottom, buffer_dc, 0,0, SRCCOPY);
}
