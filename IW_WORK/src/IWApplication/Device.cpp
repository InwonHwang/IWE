#include "Device.h"

CDevice::CDevice()
	: _D3D(0),
	_D3DDevice(0),
	_hWnd(0)
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
	_D3D = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = _hWnd;    // set the window to be used by Direct3D


								   // create a device class using this information and the info from the d3dpp stuct
	_D3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&_D3DDevice);

	return true;
}

void CDevice::Release()
{
	SAFE_RELEASE(_D3DDevice);
	SAFE_RELEASE(_D3D);
}
