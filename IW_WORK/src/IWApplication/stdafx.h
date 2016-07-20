#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dxfile.h>
#include <string>
#include <map>



#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

void DebugBox(HRESULT, LPCSTR);