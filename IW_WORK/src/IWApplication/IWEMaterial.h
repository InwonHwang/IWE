#pragma once
#include "stdafx.h"

class Material
{
public:
	LPDIRECT3DTEXTURE9 _texture;
	D3DMATERIAL9 _matD3D;
	

public:
	Material();
	~Material();	
};

