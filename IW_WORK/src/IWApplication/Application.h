#pragma once
#include "stdafx.h"
#include "Mesh.h"

class CWindowManager;


class CApplication
{
private:
	CWindowManager *_wndManager;

	//Test
	CMesh *_mesh;
	CSkinnedMesh *_mesh2;
	void DrawFrame(CMesh* mesh);
	void DrawFrame2(CSkinnedMesh* mesh);

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

