#pragma once
#include "stdafx.h"

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

class MESH
{
public:
	char*               _name;
	D3DXMESHDATA*      _meshData;

	DWORD           _numMaterials;
	MATERIAL*       _materials;

public:
	MESH() : _name(NULL), _meshData(NULL), _materials(NULL), _numMaterials(0)
	{
		_meshData = new D3DXMESHDATA();
	}
	~MESH()
	{
		RELEASE_COM(_meshData->pMesh);
		RELEASE_COM(_meshData->pPatchMesh);
		RELEASE_COM(_meshData->pPMesh);
		SAFE_DELETE(_meshData);
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE_ARRAY(_materials);		
	}

};

class CGameObject
{
public :
	char * _name;
	MESH * _mesh;

	CGameObject() : _name(NULL), _mesh(NULL)
	{
	}
	~CGameObject()
	{
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE(_mesh);
	}
};

class FRAME
{
public:
	char*   _name;
	MESH*   _mesh;
	FRAME*  _child;

	FRAME() : _name(NULL), _mesh(NULL), _child(NULL)
	{
	}

	~FRAME()
	{
		SAFE_DELETE_ARRAY(_name);
		SAFE_DELETE(_mesh);
		SAFE_DELETE(_child);
	}
};

