#pragma once
#include "stdafx.h"
#include "WindowManager.h"

class CWindowManager;
class GameObject;
class AnimationSet;

class CApplication : public CWindowManager
{
private:
	GameObject *_root;
	AnimationSet *_animSet;
	
private:	
	void update();
	void draw();
	void DrawFrame2(GameObject* gameObject);

public:
	CApplication();
	~CApplication();
		
	bool init();
	void frame();
	void shutDown();
	void go();
};

