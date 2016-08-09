#pragma once
#include "stdafx.h"

class GameObject;

class Transform
{
public:
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;

	D3DXMATRIX matrix;
	GameObject* gameObject;

	void update();

public:
	Transform();
	~Transform();

};

//class Transform
//{
//public:
//	D3DXVECTOR3 position;
//	D3DXQUATERNION rotation;
//	D3DXVECTOR3 scale;
//	
//	D3DXMATRIX matrix;
//	GameObject* gameObject;
//	
//	void update();
//
//public:
//	Transform();
//	~Transform();
//	
//};

