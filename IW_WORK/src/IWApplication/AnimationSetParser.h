#pragma once
#include "IXParser.h"
#include "stdafx.h"

class CAnimationSet;

class CAnimationSetParser : public IXParser
{
private:
	void parseXFileData(ID3DXFileData* pFileData, void ** ppData) override;
	void parseXFile(char* filename, void **ppData) override;

public:
	CAnimationSetParser();
	~CAnimationSetParser();

	CAnimationSet* parse(char *filename);
};

