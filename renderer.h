#ifndef REND_H
#define REND_H

#include <windows.h>   
#include <windowsx.h>  
#include "simulator.h"
#include "wincore.h"
#include "pbody.h"

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
	POINT pnt[3];
	int c;
	pbody *pb;
	void draw_triangle(POINT cnt[3], HBRUSH *brsh, HPEN *pn);
	pbody *tmp;
public:
	renderer() {c = 0;};
	void init(simulator *s);
	void Draw();
	virtual ~renderer() {}
	LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	POINT mouse;
	
};

#endif //REND_H