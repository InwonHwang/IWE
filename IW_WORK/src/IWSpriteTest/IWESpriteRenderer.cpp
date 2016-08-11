#include "IWESpriteRenderer.h"
#include "IWESprite.h"
#include "IWETexture.h"
#include "IWEGameObject.h"
#include "IWETransform.h"
#include "Device.h"


IWESpriteRenderer::IWESpriteRenderer()
	: _sprite(NULL)	
{	
}


IWESpriteRenderer::~IWESpriteRenderer()
{
}

void IWESpriteRenderer::setSprite(const IWESprite& sprite)
{
	_sprite = const_cast<IWESprite *>(&sprite);
}
void IWESpriteRenderer::setColor(const D3DXCOLOR& color)
{
	_color = color;
}
void IWESpriteRenderer::update()
{
	//D3DXVECTOR3 center(_sprite->getCenter().x(), _sprite->getCenter().y(), _sprite->getCenter().z());	
	//D3DXVECTOR3 position; 
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(50.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
	g_Sprite->Draw(_sprite->getTexture()->_d3dTexture9, NULL, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
}