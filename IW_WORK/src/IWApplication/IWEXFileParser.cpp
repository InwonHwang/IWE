#include "IWEXFileParser.h"
#include "XFile.h"
#include "IWEXMeshParser.h"
#include "IWEXAnimationParser.h"
#include "IWEXTransformMatrixParser.h"
#include "IWEMesh.h"
#include "IWEAnimation.h"
#include "IWEAnimationSet.h"
#include "IWETransform.h"
#include "IWEGameObject.h"

XFileParser::XFileParser()
	: meshParser(NULL),
	loaderMatrix(NULL),
	animationParser(NULL),
	_root(NULL)
{
	meshParser = new XMeshParser();
	animationParser = new XAnimationParser();
	loaderMatrix = new XTransformMatrixParser();
}


XFileParser::~XFileParser()
{
	/*for (std::list<AnimationSet *>::iterator it = _animationSets.begin(); it != _animationSets.end(); it++)
		SAFE_DELETE((*it));
	_animationSets.clear();*/

	SAFE_DELETE(meshParser);
	SAFE_DELETE(animationParser);
	SAFE_DELETE(loaderMatrix);
}

HRESULT XFileParser::getGUID(LPD3DXFILEDATA pXFileData, GUID *guid)
{
	HRESULT hr = pXFileData->GetType(guid);
		
	return hr;
}

HRESULT XFileParser::getName(LPD3DXFILEDATA pXFileData, char **name)
{
	DWORD size = 0;
	HRESULT hr = 0;	

	if (FAILED(hr = pXFileData->GetName(NULL, &size)))
		return hr;		

	if (size != 0)
	{
		*name = new char[size];
		if (FAILED(hr = pXFileData->GetName(*name, &size)))
			return hr;
	}

	if (name == NULL)
	{
		*name = new char[11];

		strcpy_s(*name, 10, "GameObject");
	}

	return hr;
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
	_root = new GameObject();

	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA data = NULL;

		if (FAILED(hr = pEnumObject->GetChild(i, &data)))
		{
			DebugError(hr);
			break;
		}		

		parseXFileData(data, (LPVOID *)&_root);

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
		GameObject * newGameObject = new GameObject();
		getName(pXFileData, &newGameObject->name);		

		if (ppData)
		{
			GameObject *parent = *((GameObject **)ppData);

			parent->transform->_children.push_back(newGameObject->transform);
			newGameObject->transform->_parent = parent->transform;
		}
		ppData = (LPVOID *)&newGameObject;
	}
	else if (type == TID_D3DRMFrameTransformMatrix)
	{		
		loadTransform(pXFileData, ppData);
	}
	else if (type == TID_D3DRMMesh)
	{		
		loadMesh(pXFileData, ppData);
	}
	else if (type == TID_D3DRMAnimationSet)
	{
		AnimationSet * animSet = new AnimationSet();
		_animationSets.push_back(animSet);			
	}
	else if (type == TID_D3DRMAnimation)
	{
		loadAnimation(pXFileData, ppData);
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

void XFileParser::loadMesh(LPD3DXFILEDATA pXFileData, void **ppData)
{	
	Mesh *tmpMesh = meshParser->getData(pXFileData, ppData);
	
	if (ppData && tmpMesh)
	{
		GameObject *tmpGameObject = *((GameObject **)ppData);					
		tmpGameObject->mesh = tmpMesh;
		
	}
	else 
		SAFE_DELETE(tmpMesh);
}

void XFileParser::loadAnimation(LPD3DXFILEDATA pXFileData, void **ppData)
{
	Animation * animation = animationParser->getData(pXFileData, ppData);

	if (animation)
	{	
		_animationSets.back()->addAnimation(animation);
	}		
}

void XFileParser::loadTransform(LPD3DXFILEDATA pXFileData, void **ppData)
{
	D3DXMATRIX tmpMatrix = loaderMatrix->getData(pXFileData, ppData);

	if (ppData && tmpMatrix)
	{
		GameObject *tmpGameObject = *((GameObject **)ppData);
		tmpGameObject->transform->_matrix = tmpMatrix;
	}
}


