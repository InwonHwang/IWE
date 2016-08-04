#pragma once
#include "ILoadXFile.h"
#include "stdafx.h"



class LoadXTransformMatrix : public ILoadXFile
{
private:
	std::unique_ptr<D3DXMATRIX> _matrix;
	
public:
	LoadXTransformMatrix();
	~LoadXTransformMatrix();

	D3DXMATRIX *getData();
	bool loadData(LPD3DXFILEDATA pXFileData, void ** ppData) override;
};

