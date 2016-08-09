#include "IWEAnimationSet.h"
#include "IWEAnimation.h"

AnimationSet::AnimationSet()
	: _frameTime(0),
	_length(0)
{
	_animation.clear();
}

AnimationSet::~AnimationSet()
{
	for (std::list<Animation *>::iterator it = _animation.begin(); it != _animation.end(); it++)
		SAFE_DELETE((*it));
	_animation.clear();
}

DWORD AnimationSet::getFrameTime()
{	
	return _frameTime;
}

DWORD AnimationSet::getLength()
{
	return _length;
}

void AnimationSet::addAnimation( Animation * animation)
{
	_animation.push_back(animation);
}

void AnimationSet::findBone(Transform *rootTransform)
{	
	for (std::list<Animation *>::iterator it = _animation.begin(); it != _animation.end(); ++it)
	{
		(*it)->findBone(rootTransform);
	}
}

void AnimationSet::update(DWORD LocalTime)
{	
	for (std::list<Animation *>::iterator it = _animation.begin(); it != _animation.end(); ++it)
	{
		(*it)->update(LocalTime);
	}
}
