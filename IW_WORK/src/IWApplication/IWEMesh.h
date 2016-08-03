#pragma once
#include "stdafx.h"

class Material;

class Mesh
{

public:
	DWORD				 _numMaterials;

	LPD3DXMESHDATA		 _pMeshData;	
	LPD3DXEFFECTINSTANCE _pEffects;
	LPD3DXSKININFO		 _pSkinInfo;
	DWORD*				 _pAdjacency;
	Material*			 _materials;
	
	
public:
	Mesh();
	~Mesh();

};

