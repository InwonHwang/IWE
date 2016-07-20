#include "WindowMgr.h"
#include "Application.h"

CWindowMgr *WMHandle = 0;

CWindowMgr::CWindowMgr()
	: _hWnd(0),
	_wndName(0),
	isRunning(true)
{
}

CWindowMgr::~CWindowMgr()
{
}


HWND CWindowMgr::init(LPCWSTR appName)
{	
	_wndName = appName;
	createWindow();	

	if (_hWnd)
		WMHandle = this;

	return _hWnd;
}

void CWindowMgr::Run(CApplication *app)
{
	MSG msg;	

	while (isRunning)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (app) app->frame();
	}
}

void CWindowMgr::ShutDown()
{
	UnregisterClass(_wndName, GetModuleHandle(NULL));
	WMHandle = NULL;
	_hWnd = NULL;
}


void CWindowMgr::createWindow()
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

LRESULT CALLBACK CWindowMgr::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN :
			switch (wParam) {
			case VK_ESCAPE:
				isRunning = false;			
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