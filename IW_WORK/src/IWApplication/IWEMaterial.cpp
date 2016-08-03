#include "IWEMaterial.h"


Material::Material()
	: _texture(NULL)
{	
}


Material::~Material()
{	
	RELEASE_COM(_texture);
}