#pragma once
#include "stdafx.h"

class CWindowMgr;

class CApplication
{
private:
	CWindowMgr *_wndMgr;


private:
	
	void update();
	void draw();
	

public:
	CApplication();
	~CApplication();

	bool init();
	void frame();
	void go();
};

