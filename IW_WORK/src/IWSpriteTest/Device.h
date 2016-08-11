#pragma once
#include "stdafx.h"

class CDevice
{
private:
	LPDIRECT3D9 _D3D;
	LPDIRECT3DDEVICE9 _D3DDevice;
	LPD3DXSPRITE _D3DSprite;
	HWND _hWnd;

private:
	CDevice();

	bool initD3D();

public:	
	~CDevice();

	static CDevice * GetInstance();

	bool Init(HWND hWnd);
	void Release();

	LPDIRECT3DDEVICE9 GetDevice();	
	LPD3DXSPRITE GetSprite();
};

#define g_Device CDevice::GetInstance()->GetDevice()
#define g_Sprite CDevice::GetInstance()->GetSprite()

