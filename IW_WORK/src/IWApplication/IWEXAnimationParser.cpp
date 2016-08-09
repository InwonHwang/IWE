#include "IWEXAnimationParser.h"
#include "IWEAnimation.h"

XAnimationParser::XAnimationParser()
	: _animation(nullptr)
{
}

XAnimationParser::~XAnimationParser()
{
	_animation.reset();
}

void XAnimationParser::loadAnimationKey(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	BYTE* buffer = NULL;
	DWORD size = 0;
	HRESULT hr = 0;

	if (FAILED(hr = pXFileData->Lock(&size, (LPCVOID*)&buffer)))
	{
		DebugError(hr);
		return ;
	}

	DWORD keyType = ((DWORD*)buffer)[0];
	DWORD keyCount = ((DWORD*)buffer)[1];

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

		_animation.get()->_rotationKey = rotList;
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

		_animation.get()->_scaleKey = scaleList;
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

		_animation->_positionKey = posList;
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

		_animation->_scaleKey = scaleList;
		_animation->_rotationKey = rotList;
		_animation->_positionKey = posList;
	}
	pXFileData->Unlock();
}

void XAnimationParser::loadAnimationOptions(LPD3DXFILEDATA pXFileData, void ** ppData)
{

	BYTE* buffer = NULL;
	DWORD size = 0;
	HRESULT hr = 0;

	if (FAILED(hr = pXFileData->Lock(&size, (LPCVOID*)&buffer)))
	{
		DWORD OpenClosed = ((DWORD*)buffer)[0];
		DWORD PositionQuality = ((DWORD*)buffer)[1];

		//if (OpenClosed && ParentAnimSet) ParentAnimSet->m_Looping = true;	
		pXFileData->Unlock();
	}
}
void XAnimationParser::loadBoneName(LPD3DXFILEDATA pXFileData, void ** ppData)
{	

	getName(pXFileData, &(_animation->_boneName));	
}

Animation* XAnimationParser::getData(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	parse(pXFileData, ppData);
	return _animation.release();
}

bool XAnimationParser::parse(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	HRESULT hr = 0;
	SIZE_T childCount;
	pXFileData->GetChildren(&childCount);
	
	_animation.reset();
	_animation = std::make_unique<Animation>();
	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pSubData;
		if (FAILED(hr = pXFileData->GetChild(i, &pSubData)))
			continue;

		parseSub(pSubData, ppData);
		RELEASE_COM(pSubData);
	}

	return true;
}

bool XAnimationParser::parseSub(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	HRESULT hr = 0;
	GUID type;

	hr = getGUID(pXFileData, &type);
	
	if (type == TID_D3DRMAnimationKey)
	{
		loadAnimationKey(pXFileData, ppData);
	}
	else if (type == TID_D3DRMAnimationOptions)
	{
		loadAnimationOptions(pXFileData, ppData);
	}
	else
	{
		loadBoneName(pXFileData, ppData);
	}

	return true;
}
