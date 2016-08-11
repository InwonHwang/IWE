#include "IWETexture.h"



IWETexture::IWETexture()
	: _d3dTexture9(NULL)
{
}


IWETexture::~IWETexture()
{
	RELEASE_COM(_d3dTexture9);
}
