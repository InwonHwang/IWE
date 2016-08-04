#pragma once
#include "stdafx.h"

class Transform;
class Mesh;

class GameObject
{

public:
	char * name;
	Mesh * mesh;
	Transform * transform;

public:
	GameObject();
	~GameObject();
};

