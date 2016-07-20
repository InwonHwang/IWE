#include "Application.h"
#include "WindowManager.h"
#include "Device.h"
#include "XFileManager.h"

CApplication::CApplication()
{
}


CApplication::~CApplication()
{	
}

void CApplication::shutDown()
{
	CDevice::GetInstance()->Release();
	_wndMgr->shutDown();
	SAFE_DELETE(_wndMgr);
}

bool CApplication::init()
{
	bool ret = true;

	_wndMgr = new CWindowManager();
	WMHandle = _wndMgr;
	HWND hWnd = _wndMgr->init(L"first");
	if (hWnd == NULL) ret =  false;
	ret = CDevice::GetInstance()->Init(hWnd);

	CXFileManager test;

	test.init();

	LPD3DXFILEENUMOBJECT temp = test.getXFileEnumObject(_T("tiger.x"));

	
	SIZE_T childCount = 0;
	HRESULT hr = temp->GetChildren(&childCount);
	if (hr != S_OK)
	{
		DebugBox(hr, "GetChildren");
		SAFE_RELEASE(temp);
	}
	else
		DebugBox(childCount, "getchild");

	test.release();

	return ret;
}

void CApplication::go()
{
	_wndMgr->run(this);
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