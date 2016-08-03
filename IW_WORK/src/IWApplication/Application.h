#pragma once
#include "stdafx.h"

class CWindowManager;
class Mesh;


class CApplication
{
private:
	CWindowManager *_wndManager;
		
	void DrawFrame(Mesh* mesh);
private:
	
	void update();
	void draw();

public:
	CApplication();
	~CApplication();

	//test
	

	bool init();
	void frame();
	void shutDown();
	void go();
};

