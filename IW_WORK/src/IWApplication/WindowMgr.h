#pragma once
#include "stdafx.h"

class CApplication;

class CWindowMgr
{
	
private:	
	HWND _hWnd;	
	LPCWSTR _wndName;
	bool isRunning;

private:
	void createWindow();

public:
	CWindowMgr();
	~CWindowMgr();

	HWND init(LPCWSTR appName);
	void Run(CApplication *app);
	void ShutDown();

	LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
