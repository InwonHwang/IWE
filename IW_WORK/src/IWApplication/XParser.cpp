#include "XParser.h"
#include "Device.h"
#include "XFile.h"
#include "Mesh.h"


CXParser::CXParser()
{
}


CXParser::~CXParser()
{
}


FRAME* CXParser::parseXFile(char* filename)
{
	ID3DXFileEnumObject* enumObject = NULL;
	ID3DXFileData* data = NULL;


	if (FAILED(g_XFILE->CreateEnumObject((LPVOID)filename, DXFILELOAD_FROMFILE, &enumObject)))
	{
		return NULL;
	}

	FRAME* frame = new FRAME();

	SIZE_T num_child;

	enumObject->GetChildren(&num_child);

	for (SIZE_T i = 0; i < num_child; i++)
	{
		if (FAILED(enumObject->GetChild(i, &data)))
			return NULL;

		parseXFileData(data, frame);

		RELEASE_COM(data);
	}

	RELEASE_COM(enumObject);


	return frame;
}

void CXParser::parseXFileData(ID3DXFileData* data, FRAME* parent_frame)
{
	ID3DXFileData*  pSubData = NULL;
	ID3DXBuffer*    adjacency = NULL;

	GUID  type;
	char* name = NULL;
	DWORD size;

	MESH* mesh = NULL;
	ID3DXBuffer* material_buffer = NULL;
	D3DXMATERIAL* materials = NULL;

	// get the template type
	// retrieves the globally unique identifier (GUID) of the object's template
	if (FAILED(data->GetType(&type)))
		return;

	// get the template name (if any)
	// retrieves a pointer to a microsoft directX file object's name
	if (FAILED(data->GetName(NULL, &size)))
		return;

	if (size != 0)
	{
		if ((name = new char[size]) != NULL)
			data->GetName(name, &size);
	}

	// give template a default name if none found
	if (name == NULL)
	{
		if ((name = new char[9]) == NULL)
			return;

		strcpy_s(name, 8, "Template");
	}

	// set sub frame
	FRAME* sub_frame = parent_frame;

	// process the templates
	FRAME* frame = NULL;

	if (type == TID_D3DRMFrame)  // it is a frame
	{
		// create a new frame structure
		frame = new FRAME();

		// store the name
		frame->_name = name;
		name = NULL;

		// add to parent frame
		parent_frame->_child = frame;

		// set sub frame parent
		sub_frame = frame;
	}
	else if (type == TID_D3DRMMesh)  // it is a mesh
	{
		// create a new mesh structure
		mesh = new MESH();

		// store the name
		mesh->_name = name;
		name = NULL;

		// load mesh data (as a skinned mesh)
		// loads a skin mesh from microsoft directX .x file data object
		if (FAILED(D3DXLoadSkinMeshFromXof(data, 0, g_Device, &adjacency, &material_buffer, NULL,
			&mesh->_numMaterials, &mesh->_skininfo, &mesh->_mesh)))
		{
			delete[] name;
			delete mesh;
			return;
		}

		RELEASE_COM(adjacency);

		// clone skin mesh if bones exist
		if (mesh->_skininfo != NULL && mesh->_skininfo->GetNumBones() != 0)
		{
			// clones a mesh using a flexible vertex format (FVF) code
			if (FAILED(mesh->_mesh->CloneMeshFVF(0, mesh->_mesh->GetFVF(), g_Device, &mesh->_skinmesh)))
			{
				mesh->_skininfo->Release();
				mesh->_skininfo = NULL;
			}
		}

		// load materials or create a default one if none
		if (mesh->_numMaterials == 0)
		{
			// create a default one
			mesh->_materials = new D3DMATERIAL9[1];
			mesh->_textures = new LPDIRECT3DTEXTURE9[1];

			ZeroMemory(mesh->_materials, sizeof(D3DMATERIAL9));

			mesh->_materials[0].Diffuse.r = 1.0;
			mesh->_materials[0].Diffuse.g = 1.0;
			mesh->_materials[0].Diffuse.b = 1.0;
			mesh->_materials[0].Diffuse.a = 1.0;
			mesh->_materials[0].Ambient = mesh->_materials[0].Diffuse;
			mesh->_materials[0].Specular = mesh->_materials[0].Diffuse;

			mesh->_textures[0] = NULL;

			mesh->_numMaterials = 1;
		}
		else
		{
			// load the materials
			materials = (D3DXMATERIAL*)material_buffer->GetBufferPointer();

			mesh->_materials = new D3DMATERIAL9[mesh->_numMaterials];
			mesh->_textures = new LPDIRECT3DTEXTURE9[mesh->_numMaterials];

			// set materials and textures for mesh
			for (DWORD i = 0; i < mesh->_numMaterials; i++)
			{
				mesh->_materials[i] = materials[i].MatD3D;
				mesh->_materials[i].Ambient = mesh->_materials[i].Diffuse;

				// build a texture path and load it
				if (FAILED(D3DXCreateTextureFromFileA(g_Device, materials[i].pTextureFilename, &mesh->_textures[i])))
					mesh->_textures[i] = NULL;
			}
		}

		RELEASE_COM(material_buffer);

		// set mesh to parent frame
		parent_frame->_mesh = mesh;
	}   // end if(type == TID_D3DRMMesh)
	else if (type == TID_D3DRMAnimationSet || type == TID_D3DRMAnimation || type == TID_D3DRMAnimationKey)
	{
		// skip animation sets and animations
		delete[] name;
		return;
	}

	// release name buffer
	delete[] name;

	SIZE_T num_child;
	data->GetChildren(&num_child);

	// scan for embedded templates
	for (SIZE_T i = 0; i < num_child; i++)
	{
		data->GetChild(i, &pSubData);

		// process embedded xfile data, recursive call.
		parseXFileData(pSubData, sub_frame);

		RELEASE_COM(pSubData);
	}
}