#include "IWEGameObject.h"
#include "IWETransform.h"

GameObject::GameObject()
	: name(NULL), 
	mesh(NULL),
	transform(NULL)
{
	transform = new Transform();
	transform->_gameObject = this;
}



GameObject::~GameObject()
{	
	SAFE_DELETE_ARRAY(name);
	SAFE_DELETE(mesh);	
	SAFE_DELETE(transform);
}
