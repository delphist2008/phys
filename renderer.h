#ifndef REND_H
#define REND_H

#include <windows.h>   
#include <windowsx.h>  
#include "simulator.h"
#include "wincore.h"

#define BGCLR RGB(128, 128, 255)

class renderer : public CWnd
{
	friend class simulator;
	friend class pbody;
private:
	CClientDC *screen;
	CMemDC *buffer;
	HDC screen_dc, buffer_dc;
	RECT screen_dim;
	CBitmap  buffer_bmp;
	HBRUSH bgbrush;
	HPEN bgpen;
	simulator *sim;

public:
	renderer() {};
	void init(simulator *s);
	void draw_triangle(POINT cnt[3], HBRUSH &brsh, HPEN &pn);
	void Draw();
	virtual ~renderer() {}
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			//End the program when window is destroyed
			::PostQuitMessage(0);
			break;
		}
		//Use the default message handling for remaining messages
		return WndProcDefault(uMsg, wParam, lParam);
	}
};

#endif //REND_H