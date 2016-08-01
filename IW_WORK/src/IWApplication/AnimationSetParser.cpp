#include "AnimationSetParser.h"
#include "XFile.h"
#include "AnimationSet.h"

CAnimationSetParser::CAnimationSetParser()
{
}


CAnimationSetParser::~CAnimationSetParser()
{
}

CAnimationSet* CAnimationSetParser::parse(char *filename)
{
	CAnimationSet * animationSet = nullptr;

	parseXFile(filename, reinterpret_cast<LPVOID*>(&animationSet));
}

void CAnimationSetParser::parseXFile(char* filename, void **ppData)
{
	ID3DXFileEnumObject* enumObject = NULL;
	ID3DXFileData* data = NULL;

	if (FAILED(g_XFILE->CreateEnumObject((LPVOID)filename, DXFILELOAD_FROMFILE, &enumObject)))
	{
		return;
	}

	SIZE_T childCount;
	enumObject->GetChildren(&childCount);

	for (SIZE_T i = 0; i < childCount; i++)
	{
		if (FAILED(enumObject->GetChild(i, &data)))
			return;

		parseXFileData(data, ppData);

		RELEASE_COM(data, NULL);
	}

	RELEASE_COM(enumObject);
}

void CAnimationSetParser::parseXFileData(ID3DXFileData* pFileData, void ** ppData)
{
	ID3DXBuffer* bufferMaterial = NULL;
	ID3DXBuffer* adjacency = NULL;
	CAnimationSet **parent = NULL;
	char* name = NULL;
	GUID  type;
	DWORD size;

	if (ppData)
		parent = reinterpret_cast<CAnimationSet **>(ppData);

	if (FAILED(pFileData->GetType(&type)))
		return;

	if (FAILED(pFileData->GetName(NULL, &size)))
		return;

	if (size != 0)
	{
		if ((name = new char[size]) != NULL)
			pFileData->GetName(name, &size);
	}

	if (type == TID_D3DRMAnimationSet)
	{
		if (name == NULL)
		{
			if ((name = new char[8]) == NULL) return;

			strcpy_s(name, 7, "Take001");
		}		
		CAnimationSet *animationSet = new CAnimationSet();
		animationSet->_name = name;

		*parent = animationSet;
	}
	else if (type == TID_D3DRMAnimationKey)
	{
		if (name == NULL)
		{
			if ((name = new char[9]) == NULL) return;

			strcpy_s(name, 8, "Template");
		}

		if(!(*parent))
	}
	else
		delete[] name;

	SIZE_T childCount;
	pFileData->GetChildren(&childCount);

	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pSubData;
		pFileData->GetChild(i, &pSubData);
		parseXFileData(pSubData, ppData);

		RELEASE_COM(pSubData);
	}
}




