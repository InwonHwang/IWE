#include "IWEXFileParser.h"
#include "XFile.h"
#include "IWELoadXMesh.h"
#include "IWELoadXAnimation.h"
#include "IWEMesh.h"
#include "IWEAnimation.h"
#include "IWEAnimationSet.h"




XFileParser::XFileParser()
	: loaderMesh(NULL)
{
	loaderMesh = new LoadXMesh();
	loaderAnimation = new LoadXAnimation();
}


XFileParser::~XFileParser()
{
	SAFE_DELETE(loaderMesh);
	SAFE_DELETE(loaderAnimation);
}

HRESULT XFileParser::getGUID(LPD3DXFILEDATA pXFileData, GUID *guid)
{
	HRESULT hr = pXFileData->GetType(guid);
		
	return hr;
}

HRESULT XFileParser::getName(LPD3DXFILEDATA pXFileData, char *name)
{
	DWORD size = 0;
	HRESULT hr = 0;	

	if (FAILED(hr = pXFileData->GetName(NULL, &size)))
		return hr;		

	if (size != 0)
	{
		name = new char[size];
		if (FAILED(hr = pXFileData->GetName(name, &size)))
			return hr;
	}

	if (name == NULL)
	{
		name = new char[11];			

		strcpy_s(name, 10, "GameObject");
	}
}

void XFileParser::parseXFile(char* fileName)
{
	LPD3DXFILEENUMOBJECT pEnumObject = NULL;
	HRESULT hr = 0;

	
	if (FAILED(hr = g_XFILE->CreateEnumObject((LPVOID)fileName, DXFILELOAD_FROMFILE, &pEnumObject)))
	{
		DebugError(hr);
		return;
	}

	SIZE_T childCount = 0;
	pEnumObject->GetChildren(&childCount);
	
	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA data = NULL;

		if (FAILED(hr = pEnumObject->GetChild(i, &data)))
		{
			DebugError(hr);
			break;
		}		

		parseXFileData(data, NULL);

		RELEASE_COM(data);
	}
	RELEASE_COM(pEnumObject);
}
void XFileParser::parseXFileData(LPD3DXFILEDATA pXFileData, void ** ppData)
{	
	HRESULT hr = 0;	
	GUID type;

	hr = getGUID(pXFileData, &type);

	if (type == TID_D3DRMFrame)
	{
	}
	else if (type == TID_D3DRMMesh)
	{		
		loadMeshData(pXFileData, ppData);
	}
	else if (type == TID_D3DRMAnimationSet)
	{
		
	}
	else if (type == TID_D3DRMAnimationKey)
	{
		loadAnimationData(pXFileData, ppData);
	}

	SIZE_T childCount;
	pXFileData->GetChildren(&childCount);

	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pSubData;
		if (FAILED(hr = pXFileData->GetChild(i, &pSubData)))		
			continue;
		
		parseXFileData(pSubData, ppData);
		RELEASE_COM(pSubData);
	}
}

void XFileParser::loadMeshData(LPD3DXFILEDATA pXFileData, void **ppData)
{	
	//Mesh *mesh = NULL;
	/*if (loaderMesh->loadData(pXFileData, NULL))
		mesh = loaderMesh->getData();*/

}

void XFileParser::loadAnimationData(LPD3DXFILEDATA pXFileData, void **ppData)
{
	Animation * animation = NULL;
	if (loaderAnimation->loadData(pXFileData, ppData))
	{		
	}
}
