#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"
#include "IWEMesh.h"
#include "IWEMaterial.h"
#include "IWEXFileParser.h"

CApplication::CApplication()
{
}

CApplication::~CApplication()
{
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

		g_Device->EndScene();
	}

	g_Device->Present(NULL, NULL, NULL, NULL);
	g_Device->SetTexture(0, NULL);
}

void CApplication::DrawFrame(Mesh* mesh)
{
	if (mesh)
	{
		for (DWORD i = 0; i < mesh->_numMaterials; i++)
		{
			g_Device->SetMaterial(&mesh->_materials[i]._matD3D);

			g_Device->SetTexture(0, mesh->_materials[i]._texture);

			mesh->_pMeshData->pMesh->DrawSubset(i);
		}

	}
}