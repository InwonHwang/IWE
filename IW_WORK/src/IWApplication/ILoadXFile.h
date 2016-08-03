#pragma once
#include "stdafx.h"

class ILoadXFile abstract
{
public:
	virtual ~ILoadXFile() {}	

	virtual bool loadData(LPD3DXFILEDATA pXFileData, void ** ppData) = 0;
};