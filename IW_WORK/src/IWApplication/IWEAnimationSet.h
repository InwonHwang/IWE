#pragma once
#include "stdafx.h"

class Animation;
class Transform;

class AnimationSet
{
private:
	std::list<Animation*> _animation;

	DWORD _length;
	DWORD _frameTime;

public:
	AnimationSet();
	~AnimationSet();

	DWORD getFrameTime();
	DWORD getLength();
	void addAnimation(Animation * animation);
	void findBone(Transform *rootTransform);
	void update(DWORD LocalTime);
};

