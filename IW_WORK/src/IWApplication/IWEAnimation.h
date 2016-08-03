#pragma once
#include "stdafx.h"

class Transform;
class AnimationKey;

struct POSITIONKEY {
	DWORD Time;
	D3DXVECTOR3 Position;

	POSITIONKEY(DWORD time, D3DXVECTOR3 pos)
	{
		Time = time;
		Position = pos;
	}
};

struct ROTATIONKEY {
	DWORD Time;
	D3DXQUATERNION Rotation;
	ROTATIONKEY(DWORD time, D3DXQUATERNION rotation)
	{
		Time = time;
		Rotation = rotation;
	}
};

struct MATRIXKEY {
	DWORD Time;
	D3DXMATRIX Matrix;
	MATRIXKEY(DWORD time, D3DXMATRIX matrix)
	{
		Time = time;
		Matrix = matrix;
	}
};

struct SCALEKEY {
	DWORD Time;
	D3DXVECTOR3 Scale;
	SCALEKEY(DWORD time, D3DXVECTOR3 scale)
	{
		Time = time;
		Scale = scale;
	}
};

class Animation
{
private:
	std::list<POSITIONKEY*> *_positionKey;
	std::list<ROTATIONKEY*> *_rotationKey;
	std::list<SCALEKEY*>	*_scaleKey;
		
	Transform * _bone;
	char* _boneName;
	DWORD _length;
	DWORD _frameTime;

public:
	Animation(std::list<POSITIONKEY*> *, std::list<ROTATIONKEY*> *, std::list<SCALEKEY*> *);
	Animation(std::list<POSITIONKEY*> *);
	Animation(std::list<ROTATIONKEY*> *);
	Animation(std::list<SCALEKEY*> *);
	Animation();	// LoadXAnimation로 생성하는것 이외에 사용자가 생성할 수 있도록, 그리고 직접 key를 추가할 수 있도록
	~Animation();

	DWORD getFrameTime();
	DWORD getLength();
	void findBone(Transform *rootTransform);
	void update();
};


