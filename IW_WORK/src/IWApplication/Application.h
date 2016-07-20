#pragma once
#include "stdafx.h"

class CWindowManager;

class CApplication
{
private:
	CWindowManager *_wndMgr;


private:
	
	void update();
	void draw();
	

public:
	CApplication();
	~CApplication();

	bool init();
	void frame();
	void shutDown();
	void go();
};

