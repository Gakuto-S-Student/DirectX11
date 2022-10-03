/*
*	Create : 2022/10/03(ŒŽ)
*		Author : Gakuto.S
*		Update : ----/10/--()
*/
#include "Application.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Application app(1280, 780, hInstance);
	app.Init();
	while (!app.Close())
	{
		app.Update();
		app.Draw();
	}
	app.Uninit();

	return 0;
}