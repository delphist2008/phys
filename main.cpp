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
	SetTimer(rend.GetHwnd(), tmr1, 0, tmr); 
	return MyApp.Run();
	KillTimer (rend.GetHwnd(), tmr1);
}

