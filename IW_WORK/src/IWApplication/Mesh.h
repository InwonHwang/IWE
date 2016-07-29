#pragma once
#include "stdafx.h"

class CMesh;
class CSkinnedMesh;
class CTransform;
class CGameObject;
class MATERIAL;

class MATERIAL
{
public:
	D3DMATERIAL9 _matD3D;
	IDirect3DTexture9* _texture;

public:
	MATERIAL() : _texture(NULL) {}
	~MATERIAL()
	{
		RELEASE_COM(_texture);
	}

};

class CSkinnedMesh
{
public:
	char*				 _name;
	D3DXMESHDATA*		 _pMeshData;
	DWORD*				 _pAdjacency;
	LPD3DXEFFECTINSTANCE _pEffects;
	LPD3DXSKININFO		 _pSkinInfo;
	MATERIAL*			 _materials;
	DWORD				 _numMaterials;

	CSkinnedMesh*		 _pNext;	
public:	
	CSkinnedMesh() : _name(nullptr), _pMeshData(nullptr), _pAdjacency(nullptr), _pEffects(nullptr), _pNext(nullptr), _pSkinInfo(nullptr), _materials(nullptr), _numMaterials(0)
	{	
		_pMeshData = new D3DXMESHDATA();
	}

	~CSkinnedMesh()
	{
		RELEASE_COM(_pSkinInfo);
		RELEASE_COM(_pMeshData->pMesh);
		RELEASE_COM(_pMeshData->pPatchMesh);
		RELEASE_COM(_pMeshData->pPMesh);		
		SAFE_DELETE(_pMeshData);
		SAFE_DELETE(_pAdjacency);
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE_ARRAY(_materials);		
	}
};

class CMesh
{
public:
	char*				 _name;
	D3DXMESHDATA*		 _pMeshData;
	DWORD*				 _pAdjacency;
	LPD3DXEFFECTINSTANCE _pEffects;

	DWORD           _numMaterials;
	MATERIAL*       _materials;

	CMesh*			_pNext;
public:
	CMesh() : _name(nullptr), _pMeshData(nullptr), _pAdjacency(nullptr), _pEffects(nullptr), _materials(nullptr), _pNext(NULL), _numMaterials(0)
	{
		_pMeshData = new D3DXMESHDATA();		
	}
	~CMesh()
	{
		RELEASE_COM(_pMeshData->pMesh);
		RELEASE_COM(_pMeshData->pPatchMesh);
		RELEASE_COM(_pMeshData->pPMesh);		
		SAFE_DELETE(_pMeshData);
		SAFE_DELETE(_pAdjacency);
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE_ARRAY(_materials);		
	}

};

class CTransform
{
public:
	CGameObject *_gameOBject;	
	CTransform *_parent;
	std::list<CTransform *> _children;
	D3DXMATRIX _matrix;
	
public:
	CTransform() : _parent(NULL){}
	~CTransform()
	{
		_children.clear();
	}
};

class CGameObject
{
public:
	char * _name;
	CMesh * _mesh;
	CTransform transform;

public :
	CGameObject() : _name(NULL), _mesh(NULL)
	{		
		transform._gameOBject = this;		
	}
	~CGameObject()
	{
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE(_mesh);
	}
};