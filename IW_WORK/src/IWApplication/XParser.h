#pragma once
#include "stdafx.h"

class XParser abstract
{
public:
	virtual ~XParser() {}
	
protected:
	virtual bool parse(LPD3DXFILEDATA pXFileData, void ** ppData) = 0;
	virtual bool parseSub(LPD3DXFILEDATA pXFileData, void ** ppData) = 0;
	HRESULT getGUID(LPD3DXFILEDATA pXFileData, GUID *guid)
	{
		HRESULT hr = pXFileData->GetType(guid);
		return hr;
	}
	HRESULT getName(LPD3DXFILEDATA pXFileData, char **name)
	{		
		DWORD size = 0;
		HRESULT hr = 0;

		if (FAILED(hr = pXFileData->GetName(NULL, &size)))
			return hr;

		if (size != 0) {
			*name = new char[size];
			if (FAILED(hr = pXFileData->GetName(*name, &size)))
				return hr;
		}
		else {
			*name = new char[11];
			strcpy_s(*name, 10, "GameObject");
		}

		return hr;
	}

};