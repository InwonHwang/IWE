#include "XFile.h"
#include <rmxfguid.h>
#include <rmxftmpl.h>

CXFile::CXFile()
	: _D3DXFile(NULL)
{
}


CXFile::~CXFile()
{
}

CXFile * CXFile::GetInstance()
{
	static CXFile Inst;

	return &Inst;
}

bool CXFile::Init()
{
	HRESULT hr = D3DXFileCreate(&_D3DXFile);

	if (hr != S_OK)
	{
		DebugBox(hr, _T("D3DXFileCreate"));
		return FALSE;
	}

	hr = _D3DXFile->RegisterTemplates((LPVOID)D3DRM_XTEMPLATES, D3DRM_XTEMPLATE_BYTES);
	if (hr != S_OK)
	{
		DebugBox(hr, _T("RegisterTemplates"));
		SAFE_RELEASE(_D3DXFile);
		return FALSE;
	}

	return TRUE;
}

void CXFile::Release()
{
	SAFE_RELEASE(_D3DXFile);
}


LPD3DXFILE CXFile::GetXFile()
{
	return _D3DXFile;
}