#pragma once
#include "stdafx.h"

class CWindowManager;

class CApplication
{
private:
	CWindowManager *_wndManager;

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

	// ÆÄ½Ì Å×½ºÆ®
	static std::list<LPD3DXMESH> _meshes;
	static std::list<D3DMATERIAL9> _materials;
	static std::list<LPDIRECT3DTEXTURE9> _textures;

};

