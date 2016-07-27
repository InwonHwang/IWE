#pragma once
#include "stdafx.h"
#include "Mesh.h"

class CWindowManager;


class CApplication
{
private:
	CWindowManager *_wndManager;

	//Test
	FRAME *_frame;
	void DrawFrame(FRAME* frame);

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

