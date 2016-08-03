#pragma once
#include "stdafx.h"

class GameObject;
class Transform;

class Component
{
public:
	GameObject *gameObject;
	Transform *transform;
	char *name;
public:
	Component() : gameObject(NULL), transform(NULL), name(NULL) {}	
	virtual ~Component() {}
};
