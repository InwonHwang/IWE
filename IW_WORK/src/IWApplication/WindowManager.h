#pragma once
#include "stdafx.h"

class CApplication;

class CWindowManager
{
	
private:	
	HWND _hWnd;	
	LPCWSTR _wndName;

private:
	void createWindow();

public:
	CWindowManager();
	~CWindowManager();

	HWND init(LPCWSTR appName);
	void run(CApplication *app);
	void shutDown();

	LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

extern CWindowManager *WMHandle;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
