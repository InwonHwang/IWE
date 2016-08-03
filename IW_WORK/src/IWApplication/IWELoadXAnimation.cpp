#include "IWELoadXAnimation.h"
#include "IWEAnimation.h"

LoadXAnimation::LoadXAnimation()
	: _animation(nullptr)
{
}

LoadXAnimation::~LoadXAnimation()
{
	_animation.reset();
}

Animation* LoadXAnimation::getData()
{
	return _animation.release();
}

bool LoadXAnimation::loadData(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	BYTE* buffer = NULL;
	DWORD size = 0;	
	HRESULT hr = 0;

	if (FAILED(hr = pXFileData->Lock(&size, (LPCVOID*)&buffer)))
	{
		DebugError(hr);
		return false;
	}

	DWORD keyType = ((DWORD*)buffer)[0];
	DWORD keyCount = ((DWORD*)buffer)[1];

	DebugBox(keyType, "keyType");
	DebugBox(keyCount, "keyCount");

	if (keyType == 0)
	{
		std::list<ROTATIONKEY *> *rotList = new std::list<ROTATIONKEY *>();
		ROTATIONKEY *rotKeys = (ROTATIONKEY*)(buffer + (sizeof(DWORD) * 2));
		for (DWORD Key = 0; Key < keyCount; Key++)
		{
			std::unique_ptr<ROTATIONKEY> tmpRotKey = std::make_unique<ROTATIONKEY>(rotKeys->Time, rotKeys->Rotation);
			
			rotList->push_back(tmpRotKey.release());
			rotKeys++;
		}

		_animation.reset(new Animation(rotList));

		delete rotList;
	}

	if (keyType == 1)
	{
		std::list<SCALEKEY *> *scaleList = new std::list<SCALEKEY *>();
		SCALEKEY* scaleKey = (SCALEKEY*)(buffer + (sizeof(DWORD) * 2));
		for (DWORD key = 0; key < keyCount; key++)
		{
			
			std::unique_ptr<SCALEKEY> tmpScaleKey = std::make_unique<SCALEKEY>(scaleKey->Time, scaleKey->Scale);

			scaleList->push_back(tmpScaleKey.release());
			scaleKey++;
		}

		_animation.reset(new Animation(scaleList));

		delete scaleList;
	}

	else if (keyType == 2)
	{
		std::list<POSITIONKEY *> *posList = new std::list<POSITIONKEY *>();
		POSITIONKEY* posKeys = (POSITIONKEY*)(buffer + (sizeof(DWORD) * 2));
		for (DWORD key = 0; key < keyCount; key++)
		{
			
			std::unique_ptr<POSITIONKEY> tmpScaleKey = std::make_unique<POSITIONKEY>(posKeys->Time, posKeys->Position);

			posList->push_back(tmpScaleKey.release());
			posKeys++;
		}

		_animation.reset(new Animation(posList));

		delete posList;
	}
	else if (keyType == 4)
	{
		std::list<POSITIONKEY *> *posList = new std::list<POSITIONKEY *>();
		std::list<ROTATIONKEY *> *rotList = new std::list<ROTATIONKEY *>();
		std::list<SCALEKEY *> *scaleList = new std::list<SCALEKEY *>();
		MATRIXKEY* matrixKeys = (MATRIXKEY*)(buffer + (sizeof(DWORD) * 2));
		for (DWORD key = 0; key < keyCount; key++)
		{
			D3DXVECTOR3 pos;
			D3DXQUATERNION rot;
			D3DXVECTOR3 scale;
			D3DXMatrixDecompose(&scale, &rot, &pos, &(matrixKeys->Matrix));
			std::unique_ptr<POSITIONKEY> tmpPosKey = std::make_unique<POSITIONKEY>(matrixKeys->Time, pos);
			std::unique_ptr<ROTATIONKEY> tmpRotKey = std::make_unique<ROTATIONKEY>(matrixKeys->Time, rot);
			std::unique_ptr<SCALEKEY> tmpScaleKey = std::make_unique<SCALEKEY>(matrixKeys->Time, scale);

			posList->push_back(tmpPosKey.release());
			rotList->push_back(tmpRotKey.release());
			scaleList->push_back(tmpScaleKey.release());
			matrixKeys++;
		}

		_animation.reset(new Animation(posList, rotList, scaleList));

		delete posList;
		delete rotList;
		delete scaleList;
	}	
	pXFileData->Unlock();

	return true;
}
