#pragma once
#include "stdafx.h"

class Material;
class Transform;

class Mesh
{

public:
	DWORD				 _numMaterials;

	LPD3DXMESHDATA		 _pMeshData;
	LPD3DXMESHDATA		 _pSkinnedMeshData;
	LPD3DXEFFECTINSTANCE _pEffects;
	LPD3DXSKININFO		 _pSkinInfo;
	DWORD*				 _pAdjacency;
	Material*			 _materials;

	LPD3DXMATRIX *		 _BoneMatrices;
	Transform *			 _transform;
	
	void update();
	void findBone(Transform *);
	
public:
	Mesh();
	~Mesh();

};

