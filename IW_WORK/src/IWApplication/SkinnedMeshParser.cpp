#include "SkinnedMeshParser.h"
#include "Mesh.h"
#include "XFile.h"
#include "Device.h"

CSkinnedMesh* CSkinnedMeshParser::parse(char *filename)
{	
	parseXFile(filename, NULL);

	if (_skinnedMeshes.size() == 0) return nullptr;

	CSkinnedMesh *skinnedMesh = _skinnedMeshes.front(); 
	CSkinnedMesh * cur = NULL;
	CSkinnedMesh * prev = NULL;	
	for (std::list<CSkinnedMesh *>::iterator it = _skinnedMeshes.begin(); it != _skinnedMeshes.end(); ++it)
	{
		cur = (*it);
		if (prev)
		{
			prev->_pNext = cur;
			prev = cur;
		}
		prev = cur;		
	}
	_skinnedMeshes.clear();

	return skinnedMesh;
}

void CSkinnedMeshParser::parseXFile(char* filename, void ** ppData)
{
	ID3DXFileEnumObject* enumObject = NULL;
	ID3DXFileData* data = NULL;

	if (FAILED(g_XFILE->CreateEnumObject((LPVOID)filename, DXFILELOAD_FROMFILE, &enumObject)))
	{
		return;
	}

	SIZE_T childCount;
	enumObject->GetChildren(&childCount);



	for (SIZE_T i = 0; i < childCount; i++)
	{		
		if (FAILED(enumObject->GetChild(i, &data)))
			return;

		GUID  type;

		if (FAILED(data->GetType(&type)))
			return;

		if(type == TID_D3DRMFrame)
			parseXFileData(data, ppData);

		RELEASE_COM(data, NULL);
	}

	RELEASE_COM(enumObject);
}

void CSkinnedMeshParser::parseXFileData(ID3DXFileData* pFileData, void ** ppData)
{
	ID3DXBuffer* bufferMaterial = NULL;
	ID3DXBuffer* adjacency = NULL;
	CSkinnedMesh* skinnedMesh = NULL;
	char* name = NULL;
	GUID  type;	
	DWORD size;



	if (FAILED(pFileData->GetType(&type)))
		return;

	if (FAILED(pFileData->GetName(NULL, &size)))
		return;

	if (size != 0)
	{
		if ((name = new char[size]) != NULL)
			pFileData->GetName(name, &size);
	}

	if (name == NULL)
	{
		if ((name = new char[9]) == NULL)
			return;

		strcpy_s(name,0, "Template");
	}

	if (type == TID_D3DRMMesh)  // it is a mesh
	{
		skinnedMesh = new CSkinnedMesh();

		skinnedMesh->_name = name;
		name = NULL;

		if (FAILED(D3DXLoadSkinMeshFromXof(pFileData, 0, g_Device, &adjacency, &bufferMaterial, NULL,
			&skinnedMesh->_numMaterials, &skinnedMesh->_pSkinInfo, &skinnedMesh->_pMeshData->pMesh)))
		{
			delete[] name;
			delete skinnedMesh;
			return;
		}

		RELEASE_COM(adjacency);

		if (skinnedMesh->_pSkinInfo != NULL && skinnedMesh->_pSkinInfo->GetNumBones() != 0)
		{
			//// clones a mesh using a flexible vertex format (FVF) code
			//if (FAILED(mesh->m_mesh->CloneMeshFVF(0, mesh->m_mesh->GetFVF(), g_d3d_device, &mesh->m_skinmesh)))
			//{
			//	mesh->m_skininfo->Release();
			//	mesh->m_skininfo = NULL;
			//}
		}

		if (skinnedMesh->_numMaterials == 0)
		{
			skinnedMesh->_materials = new MATERIAL[1];

			skinnedMesh->_materials->_matD3D.Diffuse.r = 1.0f;
			skinnedMesh->_materials->_matD3D.Diffuse.g = 1.0f;
			skinnedMesh->_materials->_matD3D.Diffuse.b = 1.0f;
			skinnedMesh->_materials->_matD3D.Diffuse.a = 1.0f;
			skinnedMesh->_materials->_matD3D.Ambient = skinnedMesh->_materials->_matD3D.Diffuse;
			skinnedMesh->_materials->_matD3D.Specular = skinnedMesh->_materials->_matD3D.Diffuse;

			skinnedMesh->_numMaterials = 1;
		}
		else
		{
			D3DXMATERIAL* materials = (D3DXMATERIAL*)bufferMaterial->GetBufferPointer();

			skinnedMesh->_materials = new MATERIAL[skinnedMesh->_numMaterials];

			for (DWORD i = 0; i < skinnedMesh->_numMaterials; i++)
			{
				skinnedMesh->_materials[i]._matD3D = materials[i].MatD3D;
				skinnedMesh->_materials[i]._matD3D.Ambient = skinnedMesh->_materials[i]._matD3D.Diffuse;
				if (FAILED(D3DXCreateTextureFromFileA(g_Device, materials[i].pTextureFilename, &skinnedMesh->_materials[i]._texture)))
					skinnedMesh->_materials[i]._texture = NULL;
			}
		}

		_skinnedMeshes.push_back(skinnedMesh);

		RELEASE_COM(bufferMaterial);
	}
	else
		delete[] name;

	SIZE_T childCount;
	pFileData->GetChildren(&childCount);

	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pSubData;
		pFileData->GetChild(i, &pSubData);

		parseXFileData(pSubData, ppData);		

		RELEASE_COM(pSubData);
	}
}