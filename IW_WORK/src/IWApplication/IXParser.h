#pragma once
#include "stdafx.h"

class IXParser abstract
{
public:
	virtual ~IXParser() {};
	virtual void parseXFile(TCHAR fileName) = 0;
	virtual void parseXFileData(LPD3DXFILEDATA fileData) = 0;
};