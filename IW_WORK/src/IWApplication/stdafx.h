#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }
#define SAFE_DELETE(p) if(p) { delete p; p = NULL; }

