#ifndef REND_H
#define REND_H

#include <windows.h>   
#include <windowsx.h>  
#include "simulator.h"
#include "wincore.h"
#include "pbody.h"
#include "ui.h"
#include "helper.h"


#define BGCLR RGB(128, 128, 255)
#define DRAWBOUNDING 0

class renderer : public CWnd
{
	friend class simulator;
	friend class pbody;
	friend class ui;
private:
	CClientDC *screen;
	CMemDC *buffer;
	HDC screen_dc, buffer_dc;
	RECT screen_dim;
	CBitmap  buffer_bmp;
	HBRUSH bgbrush;
	HPEN bgpen;
	simulator *sim;
	ui * UI;
	void draw_triangle(POINT cnt[3], HBRUSH *brsh, HPEN *pn);
public:
	renderer() {};
	void init(simulator *s, ui *u);
	void Draw();
	virtual ~renderer() {};
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif //REND_H

