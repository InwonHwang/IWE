#include "Application.h"
#include "WindowMgr.h"
#include "Device.h"

CApplication::CApplication()
{
}


CApplication::~CApplication()
{
	CDevice::GetInstance()->Release();
	_wndMgr->ShutDown();
	SAFE_DELETE(_wndMgr);	
}

bool CApplication::init()
{
	bool ret = true;

	_wndMgr = new CWindowMgr();
	HWND hWnd = _wndMgr->init(L"first");
	if (hWnd == NULL) ret =  false;
	ret = CDevice::GetInstance()->Init(hWnd);

	return ret;
}

void CApplication::go()
{
	_wndMgr->Run(this);
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