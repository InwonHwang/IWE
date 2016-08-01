#pragma once
#include "stdafx.h"

struct POSITIONKEY
{
	DWORD dwTime;
	DWORD dwFloatsCount;
	D3DXVECTOR3 Pos;
};

struct SCALEKEY
{
	DWORD dwTime;
	DWORD dwFloatsCount;
	D3DXVECTOR3 Scale;
};

struct ROTATIONKEY
{
	DWORD dwTime;
	DWORD dwFloatsCount;
	float w;
	float x;
	float y;
	float z;
};

struct MATRIXKEY
{
	DWORD dwTime;
	DWORD dwFloatsCount;
	D3DXMATRIX Mat;	
};

class CAnimationKey
{
private:
	int _count;
	std::list<POSITIONKEY *> _positionKeys;
	std::list<ROTATIONKEY *> _rotationKeys;
	std::list<ROTATIONKEY *> _scaleKeys;

public:
	char * _name;

public:
	CAnimationKey();
	~CAnimationKey();

	void update();
	void findBone();
};

