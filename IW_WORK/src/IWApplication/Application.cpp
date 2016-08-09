#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"
#include "IWEMesh.h"
#include "IWEMaterial.h"
#include "IWEXFileParser.h"
#include "IWEGameObject.h"
#include "IWETransform.h"
#include "IWEAnimationSet.h"
#include "IWEAnimation.h"

void Clear(GameObject *gameObject)
{
	for (std::list<Transform *>::iterator it = gameObject->transform->_children.begin(); it != gameObject->transform->_children.end(); it++)
	{		
		if ((*it)->_gameObject)
			Clear((*it)->_gameObject);
	}
	SAFE_DELETE(gameObject);
}

CApplication::CApplication()
	: CWindowManager()
{
}

CApplication::~CApplication()
{
	shutDown();
}

void CApplication::shutDown()
{
	CWindowManager::shutDown();
	Clear(_root);
	
	CDevice::GetInstance()->Release();
	CXFile::GetInstance()->Release();

}

bool CApplication::init()
{
	CWindowManager::init(L"Test");
	
	if (_hWnd == NULL)
	{
		return false;
	}

	if (!CDevice::GetInstance()->Init(_hWnd)) return false;
	if (!CXFile::GetInstance()->Init()) return false;

	D3DXMATRIX mat_proj, mat_view;	
	D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI / 4.0f, 1.33333f, 1.0f, 1000.0f);
	g_Device->SetTransform(D3DTS_PROJECTION, &mat_proj);
	D3DXMatrixLookAtLH(&mat_view,
		&D3DXVECTOR3(500.0, 500.0, -500.0),		
		&D3DXVECTOR3(0.0, 0.0, 0.0),
		&D3DXVECTOR3(0.0, 1.0, 0.0));

	g_Device->SetTransform(D3DTS_VIEW, &mat_view);

	XFileParser temp;
	_root = temp.parse("../../media/mesh/tiny.x");
	_animSet = temp.getAnimSet();
	_animSet->findBone(_root->transform);

	return true;
}

void CApplication::go()
{
	run();
}

void CApplication::frame()
{
	update();
	draw();
}

void CApplication::update()
{	
	static DWORD Time = GetTickCount();
	if (_animSet)
	{
		

		_animSet->update((GetTickCount() % 4961));

		//DebugBox((GetTickCount() % 4961), "time");

		
	}
	Time = GetTickCount();
}

void CApplication::draw()
{
	D3DXMATRIX mat_world;
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 64, 128, 255), 1.0f, 0);

	if (SUCCEEDED(g_Device->BeginScene()))
	{
		D3DXMatrixRotationY(&mat_world, 0);

		g_Device->SetTransform(D3DTS_WORLD, &mat_world);
		

		if (_root)
		{
			DrawFrame2(_root);
		}

		g_Device->EndScene();
	}

	g_Device->Present(NULL, NULL, NULL, NULL);
	g_Device->SetTexture(0, NULL);
}

void CApplication::DrawFrame2(GameObject* gameObject)
{
	if (!gameObject) return;

	Mesh *tmpMesh = gameObject->mesh;

	if (tmpMesh)
	{
		if (!tmpMesh->_BoneMatrices) tmpMesh->findBone(_root->transform);
		gameObject->transform->update();
		tmpMesh->update();
	}

	for (std::list<Transform *>::iterator it = gameObject->transform->_children.begin(); it != gameObject->transform->_children.end(); it++)
	{
		if((*it)->_gameObject)
			DrawFrame2((*it)->_gameObject);
	}
}