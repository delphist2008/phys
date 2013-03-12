#include "renderer.h"
#include "pbody.h"
#include <conio.h>

renderer rend;
simulator simul(&rend);

#define tmr1 1

void __stdcall tmr(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	simul.process();
	rend.Draw();
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    CWinApp MyApp;
    rend.Create();
	rend.init(&simul);

	POINT pnt[3];
	pnt[0].x = 100;
	pnt[0].y = 100;
	pnt[1].x = 100;
	pnt[1].y = 300;
	pnt[2].x = 300;
	pnt[2].y = 300;
	pbody pb(pnt, RGB(255,30,30), 4, &simul);
	pb.setAV(0.02f);
	SetTimer(rend.GetHwnd(), tmr1, 0, tmr); 
    return MyApp.Run();
	KillTimer (rend.GetHwnd(), tmr1);
}

