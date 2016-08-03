#include "IWEMesh.h"


Mesh::Mesh()
	: _pMeshData(NULL),	
	_pEffects(NULL),
	_pSkinInfo(NULL),
	_pAdjacency(NULL),
	_materials(NULL),
	_numMaterials(0)
{
	_pMeshData = new D3DXMESHDATA();
}


Mesh::~Mesh()
{		
	RELEASE_COM(_pSkinInfo);
	RELEASE_COM(_pMeshData->pMesh);
	RELEASE_COM(_pMeshData->pPatchMesh);
	RELEASE_COM(_pMeshData->pPMesh);
	SAFE_DELETE(_pMeshData);
	SAFE_DELETE(_pAdjacency);
	SAFE_DELETE_ARRAY(_materials);
}
