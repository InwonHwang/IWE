#pragma once
#include "stdafx.h"

class IXParser abstract
{
protected:
	virtual void parseXFile(char* fileName) = 0;
	virtual void parseXFileData(LPD3DXFILEDATA fileData) = 0;

public:
	virtual ~IXParser() {};		
	
};