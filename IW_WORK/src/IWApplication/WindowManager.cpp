#include "WindowManager.h"
#include "Application.h"

CWindowManager *WMHandle = 0;

CWindowManager::CWindowManager()
	: _hWnd(0),
	_wndName(0)
{
}

CWindowManager::~CWindowManager()
{
}

HWND CWindowManager::init(LPCWSTR appName)
{	
	_wndName = appName;
	createWindow();	

	return _hWnd;
}

void CWindowManager::run(CApplication *app)
{
	MSG msg;

	while (true)		
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
		
		if (app) app->frame();
	}
}

void CWindowManager::shutDown()
{
	UnregisterClass(_wndName, GetModuleHandle(NULL));
	WMHandle = NULL;
	_hWnd = NULL;
}


void CWindowManager::createWindow()
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _wndName;		

	RegisterClassEx(&wc);

	_hWnd = CreateWindowEx(NULL,
		_wndName,
		_wndName,
		WS_OVERLAPPEDWINDOW,
		300, 300,
		800, 600,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
		
	ShowWindow(_hWnd, SW_SHOWNORMAL);
}

LRESULT CALLBACK CWindowManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN :
			switch (wParam) {
			case VK_ESCAPE:
				PostMessage(GetActiveWindow(), WM_QUIT, NULL, NULL);
			}
			break;

		case WM_DESTROY:	
			PostQuitMessage(0);
			return 0;
		 break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:		
			PostQuitMessage(0);
			return 0;
		break;

		default:
			WMHandle->MsgProc(hWnd, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}