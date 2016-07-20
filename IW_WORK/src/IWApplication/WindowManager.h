#pragma once
#include "stdafx.h"

class CApplication;

class CWindowManager
{
	
private:	
	HWND _hWnd;	
	LPCTSTR _wndName;
	bool isRunning;

private:
	void createWindow();

public:
	CWindowManager();
	~CWindowManager();

	HWND init(LPCTSTR appName);
	void run(CApplication *app);
	void shutDown();

	LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

extern CWindowManager *WMHandle;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
