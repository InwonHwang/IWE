#include "stdafx.h"

void DebugBox(HRESULT hr, LPCSTR funcName)
{
	char szBuffer[50];
	sprintf_s(szBuffer, "%i", hr);
	MessageBoxA(GetActiveWindow(), szBuffer, funcName, MB_OK);
}