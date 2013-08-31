#include "renderer.h"
#include "pbody.h"
#include "ui.h"
#include "simulator.h"
#include <conio.h>

#define tmr1 1

renderer rend;
ui UI;
simulator simul;

void __stdcall tmr(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	simul.process();
	UI.update();
	rend.Draw();
}

// Global function which converts integer to binary
// and dump to the output window.
void DumpBinary( DWORD Value )
{
    // Buffer to hold the converted string.
    TCHAR Buffer[255] = { 0 };

    // Convert the value to binary string.
    _itot( Value, Buffer, 2 );

    // Display to output window.
    CString csMessage;
    csMessage.Format( _T("\n%d in binary: %s"), Value, Buffer );
    OutputDebugString( csMessage );
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	int z;
	int c;
	c = 255;
	z  = (((c & 4) << 5)  | ((c & 8) << 3)  | ((c & 16) << 1) | ((c & 32) >> 1)) ;
	CWinApp MyApp;
	rend.Create();
	rend.init(&simul, &UI);
	simul.init(&rend, &UI);
	UI.init(&simul, &rend);
	SetTimer(rend.GetHwnd(), tmr1, 0, tmr); 
	return MyApp.Run();
	KillTimer (rend.GetHwnd(), tmr1);
}