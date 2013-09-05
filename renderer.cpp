#include "renderer.h"
using namespace std;

void renderer::init(simulator *s, ui *u)
{
	sim = s;
	UI = u;
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
}

void renderer::draw_triangle(vec2 cnt[3], HBRUSH *brsh, HPEN *pn, HPEN *cp, int ce)
{
	SelectBrush(buffer_dc, *brsh);
	SelectPen(buffer_dc, *pn);
	cntt[0].x = cnt[0].x;
	cntt[0].y = cnt[0].y;
	cntt[1].x = cnt[1].x;
	cntt[1].y = cnt[1].y;
	cntt[2].x = cnt[2].x;
	cntt[2].y = cnt[2].y;
	Polygon(buffer_dc, cntt, 3);
	if (ce) 
	{
		SelectPen(buffer_dc, *cp);
		MoveToEx(buffer_dc, cnt[ce-1].x, cnt[ce-1].y, NULL);
		LineTo(buffer_dc, cnt[ce%3].x, cnt[ce%3].y);
	}
}

int _n;
int XX, YY;
float x, y;
POINT frc;

void renderer::Draw()
{
	SelectBrush(buffer_dc, bgbrush);
	SelectPen(buffer_dc, bgpen);
	Rectangle(buffer_dc, 0, 0, screen_dim.right, screen_dim.bottom);
	for (sim->it = sim->bodies.begin(); sim->it < sim->bodies.end(); ++sim->it)
		(*sim->it)->draw();

	if (UI->state == RMBB)
	{
		SelectPen(buffer_dc, bgpen);
		MoveToEx(buffer_dc, UI->impulse_line_begin.x, UI->impulse_line_begin.y, NULL);
		LineTo(buffer_dc, UI->mouse_pos.x, UI->mouse_pos.y);
		frc.x = UI->mouse_pos.x - UI->impulse_line_begin.x;
		frc.y = UI->mouse_pos.y - UI->impulse_line_begin.y;
		for (_n = 0; _n < 3; _n++)
			if (intersect(sim->UI->body_at_click->g_countour[_n], sim->UI->body_at_click-> g_countour[(_n+1) % 3], sim->UI->impulse_line_begin, sim->UI->mouse_pos))
			{
				YY = (sim->UI->body_at_click->g_countour[_n].x  - sim->UI->body_at_click->g_countour[(_n+1) % 3].x ) ;
				XX = (sim->UI->body_at_click->g_countour[_n].y  - sim->UI->body_at_click->g_countour[(_n+1) % 3].y ) ;
				break;
			}
			XX *= -1;
			MoveToEx(buffer_dc, UI->impulse_line_begin.x, UI->impulse_line_begin.y, NULL);
			LineTo(buffer_dc, UI->impulse_line_begin.x - XX, UI->impulse_line_begin.y - YY);		
	}
	TextOutA(buffer_dc, 10,10,UI->debugstr, strlen(UI->debugstr));
	BitBlt(screen_dc, 0,0, screen_dim.right, screen_dim.bottom, buffer_dc, 0,0, SRCCOPY);
}

LRESULT renderer::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYUP:
		UI->onKeyUp(GET_WM_VKEYTOITEM_CODE(wParam, lParam));
		break;
	case WM_KEYDOWN:
		UI->onKeyDown(GET_WM_VKEYTOITEM_CODE(wParam, lParam));
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		UI->click_pos.x = (int)GET_X_LPARAM(lParam);
		UI->click_pos.y = (int)GET_Y_LPARAM(lParam);
		UI->onLMBD();
		break;
	case WM_LBUTTONUP:
		UI->onLMBU();
		break;
	case WM_MOUSEMOVE:
		UI->mouse_pos.x = (int)GET_X_LPARAM(lParam);
		UI->mouse_pos.y = (int)GET_Y_LPARAM(lParam);
		UI->onMM();
		break;
	case WM_RBUTTONDOWN:
		UI->click_pos.x = (int)GET_X_LPARAM(lParam);
		UI->click_pos.y = (int)GET_Y_LPARAM(lParam);
		UI->onRMBD();
		break;
	case WM_RBUTTONUP:
		UI->onRMBU();
		break;
	default:
		return WndProcDefault(uMsg, wParam, lParam);
		break;
	}
};