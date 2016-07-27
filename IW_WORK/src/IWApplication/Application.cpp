#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"
#include "XParser.h"



CApplication::CApplication()
{
}


CApplication::~CApplication()
{	
	shutDown();
}

void CApplication::shutDown()
{
	SAFE_DELETE(_frame);
	CDevice::GetInstance()->Release();
	CXFile::GetInstance()->Release();

	_wndManager->shutDown();
	SAFE_DELETE(_wndManager);
}

bool CApplication::init()
{
	_wndManager = new CWindowManager();

	WMHandle = _wndManager;
	HWND hWnd = _wndManager->init(L"Test");

	if (hWnd == NULL)
	{
		SAFE_DELETE(_wndManager);
		return false;
	}

	if (!CDevice::GetInstance()->Init(hWnd)) return false;
	if (!CXFile::GetInstance()->Init()) return false;

	D3DXMATRIX mat_proj, mat_view;

	// builds a left-handed perspective projection matrix based on a field of view
	D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI / 4.0, 1.33333, 1.0, 1000.0);

	// sets a single device transformation-related state
	g_Device->SetTransform(D3DTS_PROJECTION, &mat_proj);

	// create and set the view matrix
	D3DXMatrixLookAtLH(&mat_view,
		&D3DXVECTOR3(0.0, 0.0, -10.0),
		&D3DXVECTOR3(0.0, 0.0, 0.0),
		&D3DXVECTOR3(0.0, 1.0, 0.0));

	g_Device->SetTransform(D3DTS_VIEW, &mat_view);

	CXParser temp;
	_frame = temp.parseXFile("../../media/mesh/tiger.x");

	return true;
}

void CApplication::go()
{
	_wndManager->run(this);
}

void CApplication::frame()
{
	update();
	draw();
}

void CApplication::update()
{

}

void CApplication::draw()
{
	//g_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 64, 128, 255), 1.0f, 0);

	//g_Device->BeginScene();    // begins the 3D scene

	//DrawFrame(_frame);

	//g_Device->EndScene();    // ends the 3D scene

	//g_Device->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen

	D3DXMATRIX mat_world;

	// clear device back buffer
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 64, 128, 255), 1.0f, 0);

	// Begin scene
	if (SUCCEEDED(g_Device->BeginScene()))
	{
		// create and set the world transformation matrix
		// rotate object along y-axis
		D3DXMatrixRotationY(&mat_world, 0);

		g_Device->SetTransform(D3DTS_WORLD, &mat_world);

		// draw frames
		DrawFrame(_frame);

		// end the scene
		g_Device->EndScene();
	}

	// present the contents of the next buffer in the sequence of back buffers owned by the device
	g_Device->Present(NULL, NULL, NULL, NULL);

	// release texture
	g_Device->SetTexture(0, NULL);
}

void CApplication::DrawFrame(FRAME* frame)
{
	MESH* mesh;
	D3DXMATRIX* matrices = NULL;
	ID3DXMesh* mesh_to_draw;

	// return if no frame
	if (frame == NULL)
		return;

	// draw meshes if any in frame
	if ((mesh = frame->_mesh) != NULL)
	{
		// setup pointer to mesh to draw
		mesh_to_draw = mesh->_mesh;

		// generate mesh from skinned mesh to draw with
		if (mesh->_skinmesh != NULL && mesh->_skininfo != NULL)
		{
			DWORD num_bones = mesh->_skininfo->GetNumBones();

			// allocate an array of matrices to orient bones
			matrices = new D3DXMATRIX[num_bones];

			// set all bones orientation to identity
			for (DWORD i = 0; i < num_bones; i++)
				D3DXMatrixIdentity(&matrices[i]);

			// lock source and destination vertex buffers

			void* source = NULL;
			void* dest = NULL;

			// locks a vertex buffer and obtains a pointer to the vertex buffer memory
			mesh->_mesh->LockVertexBuffer(0, &source);
			mesh->_skinmesh->LockVertexBuffer(0, &dest);

			// update skinned mesh, applies software skinning to the target vertices based on the current matrices.
			mesh->_skininfo->UpdateSkinnedMesh(matrices, NULL, source, dest);

			// unlock buffers
			mesh->_skinmesh->UnlockVertexBuffer();
			mesh->_mesh->UnlockVertexBuffer();

			// point to skin mesh to draw
			mesh_to_draw = mesh->_skinmesh;
		}

		// render the mesh
		for (DWORD i = 0; i < mesh->_numMaterials; i++)
		{
			// set the materials properties for the device
			g_Device->SetMaterial(&mesh->_materials[i]);

			// assigns a texture to a stage for a device
			g_Device->SetTexture(0, mesh->_textures[i]);

			// draw a subset of a mesh
			mesh_to_draw->DrawSubset(i);
		}

		// free array of matrices
		delete[] matrices;
		matrices = NULL;
	}

	// draw child frames, recursively call.
	DrawFrame(frame->_child);
}