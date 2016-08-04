#include "IWETransform.h"

Transform::Transform()
	: _parent(NULL)
{
}

Transform::~Transform()
{
	SAFE_DELETE(_matrix);
	_children.clear();	
}