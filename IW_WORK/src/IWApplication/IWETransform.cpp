#include "IWETransform.h"
#include "IWEGameObject.h"

Transform::Transform()
	: _parent(NULL)
{
}

Transform::~Transform()
{
	_children.clear();	
}

void Transform::update()
{
	D3DXMATRIX temp = _matrix;
	Transform * p = _parent;
	while (p)
	{
		temp *= p->_matrix;
		p = p->_parent;
	}
	_pMatrix = temp;
}

Transform * Transform::findChild(Transform * transform, const char *name)
{
	if (transform->_gameObject->name && strcmp(name, transform->_gameObject->name) == 0)
	{
		return transform;
	}
	
	Transform * ret = nullptr;

	if (transform->_children.size() > 0)
	{		
		for (std::list<Transform *>::iterator it = transform->_children.begin(); it != transform->_children.end(); ++it)
		{
			if (ret) break;
				
			ret = findChild((*it), name);			
		}
	}	

	return ret;
}