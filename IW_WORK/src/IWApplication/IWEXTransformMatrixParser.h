#pragma once
#include "XParser.h"
#include "stdafx.h"

class XTransformMatrixParser : public XParser
{
private:
	D3DXMATRIX _matrix;
	
protected:
	bool parse(LPD3DXFILEDATA pXFileData, void ** ppData) override;
	bool parseSub(LPD3DXFILEDATA pXFileData, void ** ppData) { return true; }

public:
	XTransformMatrixParser();
	~XTransformMatrixParser();

	D3DXMATRIX getData(LPD3DXFILEDATA pXFileData, void ** ppData);
};

