#include "MeshParser.h"
#include "XFile.h"
#include "Device.h"
#include "Mesh.h"

CMesh* CMeshParser::parse(char *filename)
{
	parseXFile(filename, NULL);

	if (_meshes.size() == 0) return nullptr;

	CMesh *mesh = _meshes.front();
	CMesh * cur = NULL;
	CMesh * prev = NULL;
	for (std::list<CMesh *>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
	{
		cur = (*it);
		if (prev)
		{
			prev->_pNext = cur;
			prev = cur;
		}
		prev = cur;
	}
	_meshes.clear();

	return mesh;
}

void CMeshParser::parseXFile(char* filename, void **ppData)
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

		parseXFileData(data, ppData);

		RELEASE_COM(data, NULL);
	}

	RELEASE_COM(enumObject);
}

void CMeshParser::parseXFileData(ID3DXFileData* pFileData, void ** ppData)
{
	ID3DXBuffer* bufferMaterial = NULL;
	ID3DXBuffer* adjacency = NULL;
	CMesh* mesh = NULL;	
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

		strcpy_s(name, 8, "Template");
	}

	if (type == TID_D3DRMMesh)
	{
		mesh = new CMesh();

		mesh->_name = name;
		name = NULL;

		if (FAILED(D3DXLoadMeshFromXof(pFileData, 0, g_Device, &adjacency, &bufferMaterial, NULL,
			&mesh->_numMaterials, &mesh->_pMeshData->pMesh)))
		{
			delete[] name;
			delete mesh;
			return;
		}

		RELEASE_COM(adjacency);

		if (mesh->_numMaterials == 0)
		{
			mesh->_materials = new MATERIAL[1];

			mesh->_materials->_matD3D.Diffuse.r = 1.0f;
			mesh->_materials->_matD3D.Diffuse.g = 1.0f;
			mesh->_materials->_matD3D.Diffuse.b = 1.0f;
			mesh->_materials->_matD3D.Diffuse.a = 1.0f;
			mesh->_materials->_matD3D.Ambient = mesh->_materials->_matD3D.Diffuse;
			mesh->_materials->_matD3D.Specular = mesh->_materials->_matD3D.Diffuse;

			mesh->_numMaterials = 1;
		}
		else
		{
			D3DXMATERIAL* materials = (D3DXMATERIAL*)bufferMaterial->GetBufferPointer();

			mesh->_materials = new MATERIAL[mesh->_numMaterials];

			for (DWORD i = 0; i < mesh->_numMaterials; i++)
			{
				mesh->_materials[i]._matD3D = materials[i].MatD3D;
				mesh->_materials[i]._matD3D.Ambient = mesh->_materials[i]._matD3D.Diffuse;
				if (FAILED(D3DXCreateTextureFromFileA(g_Device, materials[i].pTextureFilename, &mesh->_materials[i]._texture)))
					mesh->_materials[i]._texture = NULL;
			}
		}		

		_meshes.push_back(mesh);

		mesh = NULL;
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
