#pragma once
#include "stdafx.h"

class CXFileManager
{
private:
	std::map<tstring, LPD3DXFILE> _D3DXFiles;
	std::map<tstring, LPD3DXFILEENUMOBJECT> _D3DXFileEnumObjects;

private:
	LPD3DXFILE createXFile() const;
	LPD3DXFILEENUMOBJECT createXFileEnumObject(LPD3DXFILE , tstring) const;
	

public:
	CXFileManager();
	~CXFileManager();

	bool init();
	void release();

	const LPD3DXFILEENUMOBJECT getXFileEnumObject(tstring);
};

