#pragma once
#include "stdafx.h"

class LoadXMesh;
class LoadXAnimation;
class LoadXTransformMatrix;
class AnimationSet;
class Mesh;
class Transform;
class GameObject;

class XFileParser
{
private:
	std::list<AnimationSet *> _animationSets;
	GameObject* _root;

	LoadXMesh *loaderMesh;
	LoadXAnimation *loaderAnimation;
	LoadXTransformMatrix *loaderFrame;

private:
	HRESULT getGUID(LPD3DXFILEDATA pXFileData, GUID *guid);
	HRESULT getName(LPD3DXFILEDATA pXFileData, char **name);
	void parseXFile(char* fileName);
	void parseXFileData(LPD3DXFILEDATA pXFileData, void ** ppData);

	void loadMesh(LPD3DXFILEDATA pXFileData, void **ppData);
	void loadAnimation(LPD3DXFILEDATA pXFileData, void **ppData);
	void loadTransform(LPD3DXFILEDATA pXFileData, void **ppData);

public:
	XFileParser();
	~XFileParser();

	//test
	GameObject* parse(char *fileName)
	{
		parseXFile(fileName);
		return _root;
	}
	DWORD getCount()
	{
		return _animationSets.size();
	}
};

