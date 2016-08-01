#pragma once
#include "stdafx.h"

class CAnimationKey;

class CAnimationSet
{
private:
	std::list<CAnimationKey *> _animationKeys;

public:
	char * _name;

public:
	CAnimationSet();
	~CAnimationSet();

	void addAnimationKey(CAnimationKey * animationKey);
	//void findBone();
	//void update();
};
