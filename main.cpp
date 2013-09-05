#include "renderer.h"
#include "pbody.h"
#include "ui.h"
#include "simulator.h"
#include <conio.h>

#define tmr1 1
#define tmr2 2

renderer rend;
ui UI;
simulator simul;

void __stdcall tmr(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	simul.process();
	UI.update();
	rend.Draw();
	UI.fpstmp++;
}

void __stdcall tmrfps(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	UI.fps = UI.fpstmp;
	UI.fpstmp = 0;
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CWinApp MyApp;
	rend.Create();
	rend.init(&simul, &UI);
	simul.init(&rend, &UI);
	UI.init(&simul, &rend);
	SetTimer(rend.GetHwnd(), tmr1, 0, tmr); 
	SetTimer(rend.GetHwnd(), tmr2, 1000, tmrfps); 
	return MyApp.Run();
	KillTimer (rend.GetHwnd(), tmr1);
	KillTimer (rend.GetHwnd(), tmr2);
}