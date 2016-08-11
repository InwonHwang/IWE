#pragma once
#include "stdafx.h"

class IWETexture
{
public:
	LPDIRECT3DTEXTURE9 _d3dTexture9;

public:
	IWETexture();
	~IWETexture();
};

