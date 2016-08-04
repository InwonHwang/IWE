#pragma once
#include "stdafx.h"

class CWindowManager;
class GameObject;
class Mesh;


class CApplication
{
private:
	CWindowManager *_wndManager;
	GameObject *_root;

	
private:	
	void update();
	void draw();
	void DrawFrame(Mesh* mesh);
	void DrawFrame2(GameObject* gameObject);

public:
	CApplication();
	~CApplication();
		

	bool init();
	void frame();
	void shutDown();
	void go();
};

