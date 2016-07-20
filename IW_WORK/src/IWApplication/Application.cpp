#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFile.h"

CApplication::CApplication()
{
}


CApplication::~CApplication()
{	
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
	HWND hWnd = _wndManager->init(_T("Test"));

	if (hWnd == NULL)
	{
		SAFE_DELETE(_wndManager);
		return false;
	}


	if (!CDevice::GetInstance()->Init(hWnd)) return false;
	if (!CXFile::GetInstance()->Init()) return false;


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

							 // do 3D rendering on the back buffer here

	CDevice::GetInstance()->GetDevice()->EndScene();    // ends the 3D scene

	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}