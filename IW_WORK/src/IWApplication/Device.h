#pragma once
#include "stdafx.h"

class CDevice
{
private:
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3dDev;
	HWND _hWnd;

private:
	CDevice();

	bool initD3D();

public:	
	~CDevice();

	static CDevice * GetInstance();

	bool Init(HWND hWnd);
	LPDIRECT3DDEVICE9 GetDevice();
	void Release();
};

