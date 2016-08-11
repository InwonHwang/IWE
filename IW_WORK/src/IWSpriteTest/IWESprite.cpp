#include "IWESprite.h"
#include "IWETexture.h"

IWESprite::IWESprite()
	:_texture(NULL)
{
}


IWESprite::~IWESprite()
{
}

IWETexture *IWESprite::getTexture() const
{
	return _texture;
}

RECT IWESprite::getRect() const
{
	return _rect;
}
IWEVector3 IWESprite::getCenter() const
{
	return _center;
}

void IWESprite::setTexture(const IWETexture& texture)
{
	_texture = const_cast<IWETexture *>(&texture);
}

void IWESprite::setRect(const RECT& rect)
{
	_rect = rect;
}

void IWESprite::setCenter(const IWEVector3& center)
{
	_center = center;
}
