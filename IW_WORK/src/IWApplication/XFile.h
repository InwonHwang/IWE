#pragma once
#include "stdafx.h"

class CXFile
{
private:
	LPD3DXFILE _D3DXFile;

private:
	CXFile();


public:	
	~CXFile();

	static CXFile * GetInstance();

	bool Init();
	void Release();	

	LPD3DXFILE GetXFile();
	
};

