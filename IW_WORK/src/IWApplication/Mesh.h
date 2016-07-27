#pragma once
#include "stdafx.h"

typedef struct MESH
{
	char*               _name;             // name of mesh

	ID3DXMesh*          _mesh;             // mesh object
	ID3DXMesh*          _skinmesh;         // skin mesh object
	ID3DXSkinInfo*      _skininfo;         // skin information

	DWORD               _numMaterials;    // number of materails in mesh
	D3DMATERIAL9*       _materials;        // array of materials
	IDirect3DTexture9** _textures;         // array of textures    

											// clear all structure data
	MESH()
	{
		_name = NULL;

		_mesh = NULL;
		_skinmesh = NULL;
		_skininfo = NULL;

		_numMaterials = 0;
		_materials = NULL;
		_textures = NULL;
	}

	// free all used resources
	~MESH()
	{
		delete[] _name;
		_name = NULL;

		RELEASE_COM(_mesh);
		RELEASE_COM(_skinmesh);
		RELEASE_COM(_skininfo);

		delete[] _materials;
		_materials = NULL;

		// release all textures resource
		if (_textures != NULL)
		{
			for (DWORD i = 0; i < _numMaterials; i++)
				RELEASE_COM(_textures[i]);

			delete[] _textures;
			_textures = NULL;
		}
	}

} MESH;


typedef struct FRAME
{
	char*   _name;     // frame's name
	MESH*   _mesh;     // linked list of meshes    
	FRAME*  _child;    // child frame

	FRAME()
	{
		// clear all data
		_name = NULL;
		_mesh = NULL;
		_child = NULL;
	}

	~FRAME()
	{
		// delete all used resources, including linked list of frames.
		delete[] _name;    _name = NULL;
		delete _mesh;      _mesh = NULL;
		delete _child;     _child = NULL;
	}

} FRAME;

