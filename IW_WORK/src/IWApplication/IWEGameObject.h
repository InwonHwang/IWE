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

	void update()
	{

	}

public:
	GameObject();
	~GameObject();
};

