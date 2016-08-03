#include "IWEGameObject.h"
#include "IWETransform.h"

GameObject::GameObject()
	: name(NULL), 
	mesh(NULL)
{
}



GameObject::~GameObject()
{	
	SAFE_DELETE_ARRAY(name);
	SAFE_DELETE(mesh);	
}
