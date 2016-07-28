#pragma once
#include "stdafx.h"
#include "Mesh.h"

class CWindowManager;


class CApplication
{
private:
	CWindowManager *_wndManager;

	//Test
	CGameObject *_gameObject;
	void DrawFrame(CGameObject* obj);

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

	
	static std::map<tstring, MESH *> _meshes;
};

