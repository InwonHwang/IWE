#include "IWELoadXTransformMatrix.h"
#include "IWETransform.h"


LoadXTransformMatrix::LoadXTransformMatrix()
	: _matrix(nullptr)
{
}


LoadXTransformMatrix::~LoadXTransformMatrix()
{
}

D3DXMATRIX * LoadXTransformMatrix::getData()
{
	return _matrix.release();
}

bool LoadXTransformMatrix::loadData(LPD3DXFILEDATA pXFileData, void** ppData)
{	
	_matrix.reset();
	_matrix = std::make_unique<D3DXMATRIX>();
	D3DXMATRIX* mat;
	SIZE_T Size;

	HRESULT hr = 0;
	if (SUCCEEDED(hr = pXFileData->Lock(&Size, (LPCVOID*)&mat)))
	{	
		D3DXMATRIX *temp = new D3DXMATRIX();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp->m[i][j] = mat->m[i][j];
			}
		}		
		
		_matrix.reset(temp);
		pXFileData->Unlock();
		return true;
	}
	
	return false;
}
