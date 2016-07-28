#pragma once
#include "stdafx.h"
#include "IXParser.h"

class CXParser : public IXParser
{
protected:
	void parseXFileData(ID3DXFileData* pData) override;
	void parseXFile(char* filename) override;

public:
	CXParser();
	~CXParser();

	void parse(char *filename);
};