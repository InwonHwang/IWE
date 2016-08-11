#pragma once
#include "stdafx.h"

class IWEGameObject;
class IWESprite;

class IWESpriteRenderer
{
public:
	IWEGameObject *gameObject;

private:
	IWESprite *_sprite;
	D3DXCOLOR _color;	
	//IWEMaterial

public:
	IWESpriteRenderer();
	~IWESpriteRenderer();

	void setSprite(const IWESprite& sprite);
	void setColor(const D3DXCOLOR& color);
	void update();
};

