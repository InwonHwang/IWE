#include "Device.h"

CDevice::CDevice()
	: _D3D(NULL),
	_D3DDevice(NULL),
	_hWnd(NULL)
{
}

CDevice::~CDevice()
{
}

CDevice * CDevice::GetInstance()
{
	static CDevice Inst;

	return &Inst;
}

LPDIRECT3DDEVICE9 CDevice::GetDevice()
{
	return _D3DDevice;
}

bool CDevice::Init(HWND hWnd)
{
	_hWnd = hWnd;
	
	return initD3D();
}

bool CDevice::initD3D()
{
	_D3D = Direct3DCreate9(D3D_SDK_VERSION); 

	D3DPRESENT_PARAMETERS d3dpp;  
	D3DDISPLAYMODE  display_mode;

	if (FAILED(_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode)))
		return FALSE;

	ZeroMemory(&d3dpp, sizeof(d3dpp));  
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = display_mode.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = _hWnd; 

								   
	_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&_D3DDevice);

	if (!_D3DDevice) return false;

	return true;
}

void CDevice::Release()
{
	SAFE_RELEASE(_D3DDevice);
	SAFE_RELEASE(_D3D);
}
