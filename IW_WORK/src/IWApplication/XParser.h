#pragma once
#include "stdafx.h"
#include "Mesh.h"

class CXParser
{
private:
	void parseXFileData(ID3DXFileData* pData, FRAME* parent);

public:
	CXParser();
	~CXParser();

	FRAME* parseXFile(char* filename);	
};