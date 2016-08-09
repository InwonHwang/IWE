#include "IWEXMeshParser.h"
#include "IWEMaterial.h"
#include "IWEMesh.h"
#include "Device.h"

XMeshParser::XMeshParser()
	: _mesh(nullptr)
{
}


XMeshParser::~XMeshParser()
{
	_mesh.reset();
}

Mesh * XMeshParser::getData(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	parse(pXFileData, ppData);
	return _mesh.release();
}

bool XMeshParser::parse(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	HRESULT hr = 0;
	LPD3DXBUFFER bufferMaterial = NULL;
	LPD3DXBUFFER adjacency = NULL;
	_mesh.reset();
	_mesh = std::make_unique<Mesh>();
	
	if (FAILED(hr = D3DXLoadSkinMeshFromXof(pXFileData, 0, g_Device, &adjacency, &bufferMaterial, NULL,
		&_mesh.get()->_numMaterials, &_mesh.get()->_pSkinInfo, &_mesh.get()->_pMeshData->pMesh)))
	{
		DebugError(hr);
		_mesh.reset();
		return false;
	}

	if (_mesh.get()->_pSkinInfo && _mesh.get()->_pSkinInfo->GetNumBones() != 0)
	{
		if (FAILED(hr = _mesh.get()->_pMeshData->pMesh->CloneMeshFVF(0, _mesh.get()->_pMeshData->pMesh->GetFVF(), g_Device, &_mesh.get()->_pSkinnedMeshData->pMesh)))
		{
			DebugError(hr);
		}
	}

	RELEASE_COM(adjacency)

	if (bufferMaterial == NULL)
	{
		_mesh.get()->_materials = new Material[1];

		_mesh.get()->_materials->_matD3D.Diffuse.r = 1.0f;
		_mesh.get()->_materials->_matD3D.Diffuse.g = 1.0f;
		_mesh.get()->_materials->_matD3D.Diffuse.b = 1.0f;
		_mesh.get()->_materials->_matD3D.Diffuse.a = 1.0f;
		_mesh.get()->_materials->_matD3D.Ambient = _mesh.get()->_materials->_matD3D.Diffuse;
		_mesh.get()->_materials->_matD3D.Specular = _mesh.get()->_materials->_matD3D.Diffuse;

		_mesh.get()->_numMaterials = 1;
	}
	else
	{
		D3DXMATERIAL* materials = (D3DXMATERIAL*)bufferMaterial->GetBufferPointer();
		_mesh.get()->_materials = new Material[_mesh.get()->_numMaterials];

		for (DWORD i = 0; i < _mesh.get()->_numMaterials; i++)
		{
			_mesh.get()->_materials[i]._matD3D = materials[i].MatD3D;
			_mesh.get()->_materials[i]._matD3D.Ambient = _mesh.get()->_materials[i]._matD3D.Diffuse;
			if (FAILED(D3DXCreateTextureFromFileA(g_Device, materials[i].pTextureFilename, &_mesh.get()->_materials[i]._texture)))
				_mesh.get()->_materials[i]._texture = NULL;
		}
	}

	RELEASE_COM(bufferMaterial);

	return true;
}

bool XMeshParser::parseSub(LPD3DXFILEDATA pXFileData, void ** ppData)
{
	return true;
}
