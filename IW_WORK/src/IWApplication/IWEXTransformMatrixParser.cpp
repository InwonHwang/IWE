#include "IWEXTransformMatrixParser.h"
#include "IWETransform.h"


XTransformMatrixParser::XTransformMatrixParser()
{
}


XTransformMatrixParser::~XTransformMatrixParser()
{
}

D3DXMATRIX XTransformMatrixParser::getData(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	parse(pXFileData, ppData);
	return _matrix;
}

bool XTransformMatrixParser::parse(LPD3DXFILEDATA pXFileData, void** ppData)
{	

	D3DXMATRIX* mat;
	SIZE_T Size;

	HRESULT hr = 0;
	if (SUCCEEDED(hr = pXFileData->Lock(&Size, (LPCVOID*)&mat)))
	{
		_matrix = *mat;
		pXFileData->Unlock();
		return true;
	}
	
	return false;
}

