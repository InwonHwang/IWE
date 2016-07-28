#include "XParser.h"
#include "Device.h"
#include "XFile.h"
#include "Application.h"
#include "Mesh.h"


CXParser::CXParser()
{
}


CXParser::~CXParser()
{
}

void CXParser::parse(char *filename)
{
	parseXFile(filename);
}

void CXParser::parseXFile(char* filename)
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

		parseXFileData(data);

		RELEASE_COM(data);
	}

	RELEASE_COM(enumObject);
}

void CXParser::parseXFileData(ID3DXFileData* pData)
{
	ID3DXBuffer*    adjacency = NULL;
	MESH* mesh = NULL;
	GUID  type;
	char* name = NULL;
	DWORD size;

	ID3DXBuffer* material_buffer = NULL;

	if (FAILED(pData->GetType(&type)))
		return;

	if (FAILED(pData->GetName(NULL, &size)))
		return;

	if (size != 0)
	{
		if ((name = new char[size]) != NULL)
			pData->GetName(name, &size);
	}

	if (name == NULL)
	{
		if ((name = new char[9]) == NULL)
			return;

		strcpy_s(name, 8, "Template");
	}

	if (type == TID_D3DRMMesh)  // it is a mesh
	{
		mesh = new MESH();

		mesh->_name = name;
		name = NULL;

		if (FAILED(D3DXLoadMeshFromXof(pData, 0, g_Device, &adjacency, &material_buffer, NULL,
			&mesh->_numMaterials, &mesh->_meshData->pMesh)))
		{
			delete[] name;
			delete mesh;
			return;
		}

		RELEASE_COM(adjacency);

		if (mesh->_numMaterials == 0)
		{
			mesh->_materials = new MATERIAL[1];

			mesh->_materials->_matD3D.Diffuse.r = 1.0;
			mesh->_materials->_matD3D.Diffuse.g = 1.0;
			mesh->_materials->_matD3D.Diffuse.b = 1.0;
			mesh->_materials->_matD3D.Diffuse.a = 1.0;
			mesh->_materials->_matD3D.Ambient = mesh->_materials->_matD3D.Diffuse;
			mesh->_materials->_matD3D.Specular = mesh->_materials->_matD3D.Diffuse;

			mesh->_numMaterials = 1;
		}
		else
		{
			D3DXMATERIAL* materials = (D3DXMATERIAL*)material_buffer->GetBufferPointer();

			mesh->_materials = new MATERIAL[mesh->_numMaterials];

			for (DWORD i = 0; i < mesh->_numMaterials; i++)
			{
				mesh->_materials[i]._matD3D = materials[i].MatD3D;
				mesh->_materials[i]._matD3D.Ambient = mesh->_materials[i]._matD3D.Diffuse;
				if (FAILED(D3DXCreateTextureFromFileA(g_Device, materials[i].pTextureFilename, &mesh->_materials[i]._texture)))
					mesh->_materials[i]._texture = NULL;
			}
		}
		CApplication::_meshes.insert(std::map<tstring, MESH *>::value_type(_T("tiger.x"), mesh));
		RELEASE_COM(material_buffer);
	}	
}
