#include "stdafx.h"

void DebugBox(HRESULT hr, LPCTSTR str)
{
	TCHAR szBuffer[50];
	_stprintf_s(szBuffer, _T("%i"), hr);

#ifdef UNICODE
	MessageBox(GetActiveWindow(), szBuffer, str, MB_OK);
#else
	MessageBoxA(GetActiveWindow(), szBuffer, str, MB_OK);
#endif 

}

void DebugBox(HRESULT hr, LPCSTR str)
{
	char szBuffer[50];
	sprintf_s(szBuffer, "%i", hr);


	MessageBoxA(GetActiveWindow(), szBuffer, str, MB_OK); 
}