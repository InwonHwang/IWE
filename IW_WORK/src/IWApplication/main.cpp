#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CApplication app;

	if (app.init())
		app.go();
	
	app.shutDown();
}