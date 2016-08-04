#include "IWEAnimation.h"

Animation::Animation(std::list<POSITIONKEY*> *posKey, std::list<ROTATIONKEY*> *rotKey, std::list<SCALEKEY*> *scaleKey)
	: Animation()
{
	_positionKey = posKey;
	_rotationKey = rotKey;
	_scaleKey = scaleKey;
}

Animation::Animation(std::list<POSITIONKEY*> *posKey)
	: Animation()
{
	_positionKey = posKey;
}
Animation::Animation(std::list<ROTATIONKEY*> *rotKey)
	: Animation()
{
	_rotationKey = rotKey;
}
Animation::Animation(std::list<SCALEKEY*> *scaleKey)
	: Animation()
{
	_scaleKey = scaleKey;
}

Animation::Animation()
	:
	_positionKey(NULL),
	_rotationKey(NULL),
	_scaleKey(NULL),
	_boneName(NULL),
	_bone(NULL),
	_length(0),
	_frameTime(0)
{
}

Animation::~Animation()
{	
	for (std::list<POSITIONKEY *>::iterator it = _positionKey->begin(); it != _positionKey->end(); it++)	
		SAFE_DELETE((*it));
	_positionKey->clear();
	
	for (std::list<ROTATIONKEY *>::iterator it = _rotationKey->begin(); it != _rotationKey->end(); it++)
		SAFE_DELETE((*it));
	_rotationKey->clear();

	for (std::list<SCALEKEY *>::iterator it = _scaleKey->begin(); it != _scaleKey->end(); it++)
		SAFE_DELETE((*it));
	_scaleKey->clear();

	SAFE_DELETE(_positionKey);
	SAFE_DELETE(_rotationKey);
	SAFE_DELETE(_scaleKey);
}

DWORD Animation::getFrameTime()
{
	return _frameTime;
}

DWORD Animation::getLength()
{
	return _length;
}

void Animation::findBone(Transform *rootTransform)
{

}

void Animation::update()
{

}
