#include "stdafx.h"

void DebugBox(HRESULT hr, LPCWSTR str)
{
	WCHAR szBuffer[50];
	swprintf_s(szBuffer, _T("%i"), hr);

	MessageBox(GetActiveWindow(), szBuffer, str, MB_OK);

}

void DebugBox(HRESULT hr, LPCSTR str)
{
	char szBuffer[50];
	sprintf_s(szBuffer, "%i", hr);


	MessageBoxA(GetActiveWindow(), szBuffer, str, MB_OK); 
}