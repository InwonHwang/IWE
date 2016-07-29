#pragma once
#include "stdafx.h"

class IXParser abstract
{
protected:
	virtual void parseXFile(char* fileName, void **ppData) = 0;
	virtual void parseXFileData(LPD3DXFILEDATA pFileData, void **ppData) = 0;

public:
	virtual ~IXParser() {};		
	
};