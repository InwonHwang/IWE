#pragma once
#include "stdafx.h"

class CApplication;

class CWindowManager
{
	
protected:	
	HWND _hWnd;	
	LPCWSTR _wndName;

private:
	void createWindow();

public:
	CWindowManager();
	virtual ~CWindowManager();

	void init(LPCWSTR appName);
	void run();
	virtual void shutDown();
	virtual void frame() = 0;

	LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

extern CWindowManager *WMHandle;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
