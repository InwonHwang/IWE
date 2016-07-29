#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"
#include "MeshParser.h"
#include "SkinnedMeshParser.h"


void clearMesh(CMesh *mesh)
{
	CMesh * next = mesh->_pNext;
	if (next)
		clearMesh(next);

	SAFE_DELETE(mesh);
}

void clearSkinnedMesh(CSkinnedMesh *skinnedMesh)
{
	CSkinnedMesh * next = skinnedMesh->_pNext;
	if (next)
		clearSkinnedMesh(next);

	SAFE_DELETE(skinnedMesh);
}

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
	clearMesh(_mesh);
	clearSkinnedMesh(_mesh2);
	shutDown();
}

void CApplication::shutDown()
{
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
	D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI / 4.0f, 1.33333f, 1.0f, 1000.0f);
	g_Device->SetTransform(D3DTS_PROJECTION, &mat_proj);
	D3DXMatrixLookAtLH(&mat_view,
		&D3DXVECTOR3(500.0, 500.0, -500.0),
		&D3DXVECTOR3(0.0, 0.0, 0.0),
		&D3DXVECTOR3(0.0, 1.0, 0.0));

	g_Device->SetTransform(D3DTS_VIEW, &mat_view);

	CMeshParser temp;
	_mesh = temp.parse("../../media/mesh/TF.x");

	CSkinnedMeshParser temp2;
	_mesh2 = temp2.parse("../../media/mesh/AV.x");

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
	D3DXMATRIX mat_world;

	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 64, 128, 255), 1.0f, 0);

	if (SUCCEEDED(g_Device->BeginScene()))
	{
		D3DXMatrixRotationY(&mat_world, 0);

		g_Device->SetTransform(D3DTS_WORLD, &mat_world);

		DrawFrame2(_mesh2);
		DrawFrame(_mesh);

		g_Device->EndScene();
	}

	g_Device->Present(NULL, NULL, NULL, NULL);

	g_Device->SetTexture(0, NULL);
}

void CApplication::DrawFrame2(CSkinnedMesh* skinnedMesh)
{
	D3DXMATRIX* matrices = NULL;
	if (skinnedMesh)
	{
		//if (skinnedMesh->_pSkinInfo != NULL)
		//{
		//	DWORD num_bones = skinnedMesh->_pSkinInfo->GetNumBones();

		//	// allocate an array of matrices to orient bones
		//	matrices = new D3DXMATRIX[num_bones];

		//	// set all bones orientation to identity
		//	for (DWORD i = 0; i < num_bones; i++)
		//		D3DXMatrixIdentity(&matrices[i]);

		//	// lock source and destination vertex buffers

		//	void* source = NULL;
		//	void* dest = NULL;

		//	// locks a vertex buffer and obtains a pointer to the vertex buffer memory
		//	mesh->m_mesh->LockVertexBuffer(0, &source);
		//	mesh->m_skinmesh->LockVertexBuffer(0, &dest);

		//	// update skinned mesh, applies software skinning to the target vertices based on the current matrices.
		//	mesh->m_skininfo->UpdateSkinnedMesh(matrices, NULL, source, dest);

		//	// unlock buffers
		//	mesh->m_skinmesh->UnlockVertexBuffer();
		//	mesh->m_mesh->UnlockVertexBuffer();

		//	// point to skin mesh to draw
		//	mesh_to_draw = mesh->m_skinmesh;
		//}		

		// free array of matrices
		/*delete[] matrices;
		matrices = NULL;*/

		for (DWORD i = 0; i < skinnedMesh->_numMaterials; i++)
		{
			g_Device->SetMaterial(&skinnedMesh->_materials[i]._matD3D);

			g_Device->SetTexture(0, skinnedMesh->_materials[i]._texture);

			skinnedMesh->_pMeshData->pMesh->DrawSubset(i);
		}

		DrawFrame2(skinnedMesh->_pNext);
	}
}

void CApplication::DrawFrame(CMesh* mesh)
{
	if (mesh)
	{
		for (DWORD i = 0; i < mesh->_numMaterials; i++)
		{
			g_Device->SetMaterial(&mesh->_materials[i]._matD3D);

			g_Device->SetTexture(0, mesh->_materials[i]._texture);

			mesh->_pMeshData->pMesh->DrawSubset(i);
		}

		DrawFrame(mesh->_pNext);
	}
}