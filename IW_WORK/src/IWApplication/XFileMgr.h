#pragma once
#include "stdafx.h"

class CXFileMgr
{
private:
	
	ID3DXFile  *_pXFile;
	ID3DXFileEnumObject *_pEnum;
	

public:
	CXFileMgr();
	~CXFileMgr();

	void test();
	void clear();
};

