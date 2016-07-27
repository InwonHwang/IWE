#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"
#include "ParsingTest.h"

std::list<LPD3DXMESH> CApplication::_meshes;
std::list<D3DMATERIAL9> CApplication::_materials;
std::list<LPDIRECT3DTEXTURE9> CApplication::_textures;

CApplication::CApplication()
{
}


CApplication::~CApplication()
{	
	shutDown();
}

void CApplication::shutDown()
{
	for (std::list<LPD3DXMESH>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
	{
		SAFE_RELEASE((*it));
	}

	_meshes.clear();
	_materials.clear();
	_textures.clear();

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

	ParsingTest t;

	t.test();

	D3DMATERIAL9 material;    // create the material struct	
	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white
	g_Device->SetMaterial(&material);

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
	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	CDevice::GetInstance()->GetDevice()->BeginScene();    // begins the 3D scene

	D3DXMATRIX matView;    // the view transform matrix
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 8.0f, 16.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView 

	D3DXMATRIX matProjection;    // the projection transform matrix
	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),    // the horizontal field of view
		800 / 600,    // the aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	static float index = 0.0f; index += 0.03f;    // an ever-increasing float value
	D3DXMATRIX matRotateY;    // a matrix to store the rotation for each triangle
	D3DXMatrixRotationY(&matRotateY, index);    // the rotation matrix
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &(matRotateY));    // set the world transform


	//_meshes.front()->DrawSubset(0);
	


	CDevice::GetInstance()->GetDevice()->EndScene();    // ends the 3D scene

	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}