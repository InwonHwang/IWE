#pragma once
#include "stdafx.h"

class LoadXMesh;
class LoadXAnimation;

class XFileParser
{
private:
	LoadXMesh *loaderMesh;
	LoadXAnimation *loaderAnimation;

private:
	HRESULT getGUID(LPD3DXFILEDATA pXFileData, GUID *guid);
	HRESULT getName(LPD3DXFILEDATA pXFileData, char *name);
	void parseXFile(char* fileName);
	void parseXFileData(LPD3DXFILEDATA pXFileData, void ** ppData);

	void loadMeshData(LPD3DXFILEDATA pXFileData, void **ppData);
	void loadAnimationData(LPD3DXFILEDATA pXFileData, void **ppData);

public:
	XFileParser();
	~XFileParser();

	//test
	void parse(char *fileName)
	{
		parseXFile(fileName);
	}
};

