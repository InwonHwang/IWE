#pragma once
#include "stdafx.h"
#include "Component.h"

class GameObject;

class Transform /*: public Component*/
{
public:
	GameObject *_gameObject;
	Transform *_parent;
	std::list<Transform *> _children;
	D3DXMATRIX _matrix;
	D3DXMATRIX _pMatrix;

	void update();
	static Transform * findChild(Transform *, const char *name);

public:
	Transform();
	~Transform();
	
};

