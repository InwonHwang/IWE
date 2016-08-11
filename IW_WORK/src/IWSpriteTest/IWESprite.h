#pragma once
#include "stdafx.h"

class IWETexture;

class IWESprite
{
private:
	IWETexture *_texture;
	RECT _rect;
	IWEVector3 _center;

public:
	IWESprite();
	~IWESprite();

	IWETexture *getTexture() const;
	RECT getRect() const;
	IWEVector3 getCenter() const;
	void setTexture(const IWETexture&);
	void setRect(const RECT&);
	void setCenter(const IWEVector3&);
};

