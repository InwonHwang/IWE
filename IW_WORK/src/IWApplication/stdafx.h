#pragma once

#pragma comment(lib, "DxErr.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <dxfile.h>
#include <tchar.h>
#include <string>
#include <map>
#include <list>
#include <rmxfguid.h>
#include "myrmxftmpl.h"

typedef std::basic_string<TCHAR> tstring;

#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

void DebugBox(HRESULT, LPCSTR);
void DebugBox(HRESULT, LPCWSTR);
void DebugError(HRESULT hr);