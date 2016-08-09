#include "IWEAnimation.h"
#include "IWETransform.h"
#include "IWEGameObject.h"
#include "Device.h"

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
		SAFE_DELETE_ARRAY((*it));
	_positionKey->clear();
	
	for (std::list<ROTATIONKEY *>::iterator it = _rotationKey->begin(); it != _rotationKey->end(); it++)
		SAFE_DELETE_ARRAY((*it));
	_rotationKey->clear();

	for (std::list<SCALEKEY *>::iterator it = _scaleKey->begin(); it != _scaleKey->end(); it++)
		SAFE_DELETE_ARRAY((*it));
	_scaleKey->clear();

	SAFE_DELETE(_positionKey);
	SAFE_DELETE(_rotationKey);
	SAFE_DELETE(_scaleKey);
	SAFE_DELETE_ARRAY(_boneName);
	_bone = NULL;
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
	if (_boneName && rootTransform->_gameObject->name && strcmp(rootTransform->_gameObject->name, _boneName) == 0)
	{		
		_bone = rootTransform;
		return;
	}	
	
	for (std::list<Transform *>::iterator it = rootTransform->_children.begin(); it != rootTransform->_children.end(); ++it)
	{
		if (_bone) break;
		findBone((*it));
	}
}

void Animation::update(DWORD LocalTime)
{
	if (!_bone) return;

	//DebugBox(LocalTime, "time");

	D3DXVECTOR3 ResultPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ResultScale(1.0f, 1.0f, 1.0f);
	D3DXQUATERNION ResultRot(0.0f, 0.0f, 0.0f, 1.0f);
	POSITIONKEY *positionKey1 = NULL;
	POSITIONKEY *positionKey2 = NULL;
	SCALEKEY *scalKey1 = NULL;
	SCALEKEY *scalKey2 = NULL;
	ROTATIONKEY *rotationKey1 = NULL;
	ROTATIONKEY *rotationKey2 = NULL;

	DWORD Time1, Time2;
	float LerpValue = 10;

	bool Animate = false;

	if (_scaleKey->size() > 0)
	{
		

		for (std::list<SCALEKEY *>::iterator it = _scaleKey->begin(); it != _scaleKey->end(); it++)
		{
			if ((*it)->Time >= LocalTime)
			{
				scalKey2 = (*it);

				if ((*it) == (*_scaleKey->begin()))
					scalKey1 = (*it);
				else
					scalKey1 = (*(--it));
				break;
			}

		}
		
		Time1 = scalKey1->Time;
		Time2 = scalKey2->Time;

		if ((Time2 - Time1) == 0) LerpValue = 0;
		else LerpValue = float(LocalTime - Time1) / float(Time2 - Time1);

		D3DXVec3Lerp(&ResultScale, &(scalKey1->Scale), &(scalKey2->Scale), LerpValue);

		Animate = true;
	}

	if (_rotationKey->size() > 0)
	{
		

		for (std::list<ROTATIONKEY *>::iterator it = _rotationKey->begin(); it != _rotationKey->end(); it++)
		{
			if ((*it)->Time >= LocalTime)
			{
				rotationKey2 = (*it);

				if ((*it) == (*_rotationKey->begin()))
					rotationKey1 = (*it);
				else
					rotationKey1 = (*(--it));
				break;
			}

		}

		Time1 = rotationKey1->Time;
		Time2 = rotationKey2->Time;

		if ((Time2 - Time1) == 0) LerpValue = 0;
		else LerpValue = float(LocalTime - Time1) / float(Time2 - Time1);

		Animate = true;

		D3DXQUATERNION q1, q2;

		q1.x = -rotationKey1->Rotation.x;
		q1.y = -rotationKey1->Rotation.y;
		q1.z = -rotationKey1->Rotation.z;
		q1.w = rotationKey1->Rotation.w;

		q2.x = -rotationKey2->Rotation.x;
		q2.y = -rotationKey2->Rotation.y;
		q2.z = -rotationKey2->Rotation.z;
		q2.w = rotationKey2->Rotation.w;

		D3DXQuaternionSlerp(&ResultRot, &q1, &q2, LerpValue);

		Animate = true;
	}

	//// position keys
	if (_positionKey->size() > 0)
	{		
		for (std::list<POSITIONKEY *>::iterator it = _positionKey->begin(); it != _positionKey->end(); it++)
		{
			if ((*it)->Time >= LocalTime)
			{
				positionKey2 = (*it);

				if ((*it) == (*_positionKey->begin()))
					positionKey1 = (*it);
				else
					positionKey1 = (*(--it));

				break;
			}

		}

		Time2 = positionKey2->Time;
		Time1 = positionKey1->Time;
		

		if ((Time2 - Time1) == 0) LerpValue = 0;
		else LerpValue = float(LocalTime - Time1) / float(Time2 - Time1);
		D3DXVec3Lerp(&ResultPos, &(positionKey1->Position), &(positionKey2->Position), LerpValue);

		Animate = true;
	}


	if (Animate)
	{
		
		D3DXMATRIX scaleMat;		
		D3DXMatrixScaling(&scaleMat, scalKey2->Scale.x, scalKey2->Scale.y, scalKey2->Scale.z);
		D3DXMatrixMultiply(&_bone->_matrix, &_bone->_matrix, &scaleMat);

		D3DXMATRIX rotMat;
		D3DXMatrixRotationQuaternion(&rotMat, &rotationKey2->Rotation);
		D3DXMatrixMultiply(&_bone->_matrix, &_bone->_matrix, &rotMat);

		D3DXMATRIX posMat;
		D3DXMatrixTranslation(&posMat, positionKey2->Position.x, positionKey2->Position.y, positionKey2->Position.z);
		D3DXMatrixMultiply(&_bone->_matrix, &_bone->_matrix, &posMat);
		
		g_Device->SetTransform(D3DTS_WORLD, &(_bone->_matrix)); 
		/*
		if (strcmp(_boneName, "Bip01") == 0)
		{			
			D3DXVECTOR3 tmpScale;
			D3DXVECTOR3 tmpPos;
			D3DXQUATERNION tmpQuaternion;
			D3DXMatrixDecompose(&tmpScale, &tmpQuaternion, &tmpPos, &_bone->_matrix);
			Debug(tmpPos.x, "Bip 01 Rotation");
		}*/
	}
}