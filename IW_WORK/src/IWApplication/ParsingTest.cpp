#include "ParsingTest.h"
#include "XFile.h"
#include "Application.h"
#include "Device.h"


ParsingTest::ParsingTest()
{
}


ParsingTest::~ParsingTest()
{
}

void ParsingTest::test()
{
	LPD3DXFILEENUMOBJECT pEnum = NULL;

//#define D3DXF_FILELOAD_FROMFILE     0x00L
//#define D3DXF_FILELOAD_FROMWFILE    0x01L
//#define D3DXF_FILELOAD_FROMRESOURCE 0x02L
//#define D3DXF_FILELOAD_FROMMEMORY   0x03L
	
	//HRESULT hr = g_XFILE->CreateEnumObject((LPVOID)"../../media/mesh/tiger.x", D3DXF_FILELOAD_FROMFILE, &pEnum);
	LPD3DXFILE xFile = NULL;

	HRESULT hr = D3DXFileCreate(&xFile);

	if (hr != S_OK)
	{
		DebugError(hr);
	}

	hr = xFile->RegisterTemplates((LPVOID)D3DRM_XTEMPLATES, D3DRM_XTEMPLATE_BYTES);
	if (hr != S_OK)
	{
		DebugError(hr);
		SAFE_RELEASE(xFile);
		return;
	}

	hr = xFile->CreateEnumObject((LPVOID)"../../media/mesh/warrior.x", D3DXF_FILELOAD_FROMFILE, &pEnum);
	if (hr != S_OK)
	{
		SAFE_RELEASE(xFile);
		SAFE_RELEASE(pEnum);
		DebugError(hr);
		return;
	}

	hr = xFile->RegisterEnumTemplates(pEnum);
	if (hr != S_OK)
	{		
		SAFE_RELEASE(pEnum);
		DebugError(hr);
		return;
	}
		

	SIZE_T childCount;		
	hr = pEnum->GetChildren(&childCount);
	if (hr != S_OK)
	{
		DebugError(hr);
		SAFE_RELEASE(pEnum);
		return;
	}	


	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pData = NULL;
		hr = pEnum->GetChild(i, &pData);

		if (hr != S_OK)
		{
			DebugError(hr);
			break;
		}

		GUID guid;
		hr = pData->GetType(&guid);	

		if (hr == S_OK)
		{			
			if (TID_D3DRMInfo == guid) { DebugBox(0, "TID_D3DRMInfo"); }	
			if (IsEqualGUID(guid, TID_D3DRMMesh)) { DebugBox(0, "TID_D3DRMInfo"); }
			if (TID_D3DRMVector == guid) { DebugBox(0, "TID_D3DRMVector"); }	
			if (TID_D3DRMMeshFace == guid) { DebugBox(0, "TID_D3DRMMeshFace"); }	
			if (TID_D3DRMMaterial == guid) { DebugBox(0, "TID_D3DRMMaterial"); }	
			if (TID_D3DRMMaterialArray == guid) { DebugBox(0, "TID_D3DRMMaterialArray"); }	
			if (TID_D3DRMFrame == guid) { DebugBox(0, "TID_D3DRMFrame"); }
			if (TID_D3DRMFrameTransformMatrix == guid) { DebugBox(0, "TID_D3DRMFrameTransformMatrix"); }	
			if (TID_D3DRMMeshMaterialList == guid) { DebugBox(0, "TID_D3DRMMeshMaterialList"); }				
			if (TID_D3DRMMeshTextureCoords == guid) { DebugBox(0, "TID_D3DRMMeshTextureCoords"); }
			if (TID_D3DRMMeshNormals == guid) { DebugBox(0, "TID_D3DRMMeshNormals"); }	
			if (TID_D3DRMCoords2d == guid) { DebugBox(0, "TID_D3DRMCoords2d"); }	
			if (TID_D3DRMMatrix4x4 == guid) { DebugBox(0, "TID_D3DRMMatrix4x4"); }	
			if (TID_D3DRMAnimation == guid) { DebugBox(0, "TID_D3DRMAnimation"); }	
			if (TID_D3DRMAnimationSet == guid) { DebugBox(0, "TID_D3DRMAnimationSet"); }	
			if (TID_D3DRMAnimationKey == guid) { DebugBox(0, "TID_D3DRMAnimationKey"); }	
			if (TID_D3DRMFloatKeys == guid) { DebugBox(0, "TID_D3DRMFloatKeys"); }	
			if (TID_D3DRMMaterialAmbientColor == guid) { DebugBox(0, "TID_D3DRMMaterialAmbientColor"); }	
			if (TID_D3DRMMaterialDiffuseColor == guid) { DebugBox(0, "TID_D3DRMMaterialDiffuseColor"); }	
			if (TID_D3DRMMaterialSpecularColor == guid) { DebugBox(0, "TID_D3DRMMaterialSpecularColor"); }	
			if (TID_D3DRMMaterialEmissiveColor == guid) { DebugBox(0, "TID_D3DRMMaterialEmissiveColor"); }	
			if (TID_D3DRMMaterialPower == guid) { DebugBox(0, "TID_D3DRMMaterialPower"); }	
			if (TID_D3DRMColorRGBA == guid) { DebugBox(0, "TID_D3DRMColorRGBA"); }	
			if (TID_D3DRMColorRGB == guid) { DebugBox(0, "TID_D3DRMColorRGB"); }	
			if (TID_D3DRMGuid == guid) { DebugBox(0, "TID_D3DRMGuid"); }	
			if (TID_D3DRMTextureFilename == guid) { DebugBox(0, "TID_D3DRMTextureFilename"); }	
			if (TID_D3DRMTextureReference == guid) { DebugBox(0, "TID_D3DRMTextureReference"); }	
			if (TID_D3DRMIndexedColor == guid) { DebugBox(0, "TID_D3DRMIndexedColor"); }	
			if (TID_D3DRMMeshVertexColors == guid) { DebugBox(0, "TID_D3DRMMeshVertexColors"); }	
			if (TID_D3DRMMaterialWrap == guid) { DebugBox(0, "TID_D3DRMMaterialWrap"); }	
			if (TID_D3DRMBoolean == guid) { DebugBox(0, "TID_D3DRMBoolean"); }	
			if (TID_D3DRMMeshFaceWraps == guid) { DebugBox(0, "TID_D3DRMMeshFaceWraps"); }	
			if (TID_D3DRMBoolean2d == guid) { DebugBox(0, "TID_D3DRMBoolean2d"); }	
			if (TID_D3DRMTimedFloatKeys == guid) { DebugBox(0, "TID_D3DRMTimedFloatKeys"); }	
			if (TID_D3DRMAnimationOptions == guid) { DebugBox(0, "TID_D3DRMAnimationOptions"); }	
			if (TID_D3DRMFramePosition == guid) { DebugBox(0, "TID_D3DRMFramePosition"); }	
			if (TID_D3DRMFrameVelocity == guid) { DebugBox(0, "TID_D3DRMFrameVelocity"); }	
			if (TID_D3DRMFrameRotation == guid) { DebugBox(0, "TID_D3DRMFrameRotation"); }	
			if (TID_D3DRMLight == guid) { DebugBox(0, "TID_D3DRMLight"); }	
			if (TID_D3DRMCamera == guid) { DebugBox(0, "TID_D3DRMCamera"); }	
			if (TID_D3DRMAppData == guid) { DebugBox(0, "TID_D3DRMAppData"); }	
			if (TID_D3DRMLightUmbra == guid) { DebugBox(0, "TID_D3DRMLightUmbra"); }	
			if (TID_D3DRMLightRange == guid) { DebugBox(0, "TID_D3DRMLightRange"); }	
			if (TID_D3DRMLightPenumbra == guid) { DebugBox(0, "TID_D3DRMLightPenumbra"); }	
			if (TID_D3DRMLightAttenuation == guid) { DebugBox(0, "TID_D3DRMLightAttenuation"); }	
			if (TID_D3DRMInlineData == guid) { DebugBox(0, "TID_D3DRMInlineData"); }	
			if (TID_D3DRMUrl == guid) { DebugBox(0, "TID_D3DRMUrl"); }	
			if (TID_D3DRMProgressiveMesh == guid) { DebugBox(0, "TID_D3DRMProgressiveMesh"); }	
			if (TID_D3DRMExternalVisual == guid) { DebugBox(0, "TID_D3DRMExternalVisual"); }	
			if (TID_D3DRMStringProperty == guid) { DebugBox(0, "TID_D3DRMStringProperty"); }	
			if (TID_D3DRMPropertyBag == guid) { DebugBox(0, "TID_D3DRMPropertyBag"); }	
			if (TID_D3DRMRightHanded == guid) { DebugBox(0, "TID_D3DRMRightHanded"); }
		}
		//parseChild(pData);
		SAFE_RELEASE(pData);
	}	

	SAFE_RELEASE(pEnum);
	SAFE_RELEASE(xFile);
}

void ParsingTest::parseChild(LPD3DXFILEDATA pData)
{
	SIZE_T childCount = 0;
	HRESULT hr = pData->GetChildren(&childCount);

	for (SIZE_T i = 0; i < childCount; i++)
	{
		LPD3DXFILEDATA pSubData = NULL;
		hr = pData->GetChild(i, &pSubData);
		if (hr != S_OK)
		{
			DebugBox(hr, "GetChild");
			break;
		}

		GUID guid;
		hr = pSubData->GetType(&guid);
		if (hr == S_OK)
		{
			if (TID_D3DRMInfo == guid) { DebugBox(0, "TID_D3DRMInfo"); }
			if (IsEqualGUID(guid, TID_D3DRMMesh))
			{ 
				SIZE_T size;
				void *buffer = NULL;
				hr = pData->Lock(&size, (LPCVOID *)buffer);
				if (SUCCEEDED(hr))
				{
					pData->Unlock();
				}

				DebugError(hr);
			}
			/*if (TID_D3DRMVector == guid) { DebugBox(0, "TID_D3DRMVector"); }
			if (TID_D3DRMMeshFace == guid) { DebugBox(0, "TID_D3DRMMeshFace"); }
			if (TID_D3DRMMaterial == guid) { DebugBox(0, "TID_D3DRMMaterial"); }
			if (TID_D3DRMMaterialArray == guid) { DebugBox(0, "TID_D3DRMMaterialArray"); }
			if (TID_D3DRMFrame == guid) { DebugBox(0, "TID_D3DRMFrame"); }
			if (TID_D3DRMFrameTransformMatrix == guid) { DebugBox(0, "TID_D3DRMFrameTransformMatrix"); }
			if (TID_D3DRMMeshMaterialList == guid) { DebugBox(0, "TID_D3DRMMeshMaterialList"); }
			if (TID_D3DRMMeshTextureCoords == guid) { DebugBox(0, "TID_D3DRMMeshTextureCoords"); }
			if (TID_D3DRMMeshNormals == guid) { DebugBox(0, "TID_D3DRMMeshNormals"); }
			if (TID_D3DRMCoords2d == guid) { DebugBox(0, "TID_D3DRMCoords2d"); }
			if (TID_D3DRMMatrix4x4 == guid) { DebugBox(0, "TID_D3DRMMatrix4x4"); }
			if (TID_D3DRMAnimation == guid) { DebugBox(0, "TID_D3DRMAnimation"); }
			if (TID_D3DRMAnimationSet == guid) { DebugBox(0, "TID_D3DRMAnimationSet"); }
			if (TID_D3DRMAnimationKey == guid) { DebugBox(0, "TID_D3DRMAnimationKey"); }
			if (TID_D3DRMFloatKeys == guid) { DebugBox(0, "TID_D3DRMFloatKeys"); }
			if (TID_D3DRMMaterialAmbientColor == guid) { DebugBox(0, "TID_D3DRMMaterialAmbientColor"); }
			if (TID_D3DRMMaterialDiffuseColor == guid) { DebugBox(0, "TID_D3DRMMaterialDiffuseColor"); }
			if (TID_D3DRMMaterialSpecularColor == guid) { DebugBox(0, "TID_D3DRMMaterialSpecularColor"); }
			if (TID_D3DRMMaterialEmissiveColor == guid) { DebugBox(0, "TID_D3DRMMaterialEmissiveColor"); }
			if (TID_D3DRMMaterialPower == guid) { DebugBox(0, "TID_D3DRMMaterialPower"); }
			if (TID_D3DRMColorRGBA == guid) { DebugBox(0, "TID_D3DRMColorRGBA"); }
			if (TID_D3DRMColorRGB == guid) { DebugBox(0, "TID_D3DRMColorRGB"); }
			if (TID_D3DRMGuid == guid) { DebugBox(0, "TID_D3DRMGuid"); }
			if (TID_D3DRMTextureFilename == guid) { DebugBox(0, "TID_D3DRMTextureFilename"); }
			if (TID_D3DRMTextureReference == guid) { DebugBox(0, "TID_D3DRMTextureReference"); }
			if (TID_D3DRMIndexedColor == guid) { DebugBox(0, "TID_D3DRMIndexedColor"); }
			if (TID_D3DRMMeshVertexColors == guid) { DebugBox(0, "TID_D3DRMMeshVertexColors"); }
			if (TID_D3DRMMaterialWrap == guid) { DebugBox(0, "TID_D3DRMMaterialWrap"); }
			if (TID_D3DRMBoolean == guid) { DebugBox(0, "TID_D3DRMBoolean"); }
			if (TID_D3DRMMeshFaceWraps == guid) { DebugBox(0, "TID_D3DRMMeshFaceWraps"); }
			if (TID_D3DRMBoolean2d == guid) { DebugBox(0, "TID_D3DRMBoolean2d"); }
			if (TID_D3DRMTimedFloatKeys == guid) { DebugBox(0, "TID_D3DRMTimedFloatKeys"); }
			if (TID_D3DRMAnimationOptions == guid) { DebugBox(0, "TID_D3DRMAnimationOptions"); }
			if (TID_D3DRMFramePosition == guid) { DebugBox(0, "TID_D3DRMFramePosition"); }
			if (TID_D3DRMFrameVelocity == guid) { DebugBox(0, "TID_D3DRMFrameVelocity"); }
			if (TID_D3DRMFrameRotation == guid) { DebugBox(0, "TID_D3DRMFrameRotation"); }
			if (TID_D3DRMLight == guid) { DebugBox(0, "TID_D3DRMLight"); }
			if (TID_D3DRMCamera == guid) { DebugBox(0, "TID_D3DRMCamera"); }
			if (TID_D3DRMAppData == guid) { DebugBox(0, "TID_D3DRMAppData"); }
			if (TID_D3DRMLightUmbra == guid) { DebugBox(0, "TID_D3DRMLightUmbra"); }
			if (TID_D3DRMLightRange == guid) { DebugBox(0, "TID_D3DRMLightRange"); }
			if (TID_D3DRMLightPenumbra == guid) { DebugBox(0, "TID_D3DRMLightPenumbra"); }
			if (TID_D3DRMLightAttenuation == guid) { DebugBox(0, "TID_D3DRMLightAttenuation"); }
			if (TID_D3DRMInlineData == guid) { DebugBox(0, "TID_D3DRMInlineData"); }
			if (TID_D3DRMUrl == guid) { DebugBox(0, "TID_D3DRMUrl"); }
			if (TID_D3DRMProgressiveMesh == guid) { DebugBox(0, "TID_D3DRMProgressiveMesh"); }
			if (TID_D3DRMExternalVisual == guid) { DebugBox(0, "TID_D3DRMExternalVisual"); }
			if (TID_D3DRMStringProperty == guid) { DebugBox(0, "TID_D3DRMStringProperty"); }
			if (TID_D3DRMPropertyBag == guid) { DebugBox(0, "TID_D3DRMPropertyBag"); }
			if (TID_D3DRMRightHanded == guid) { DebugBox(0, "TID_D3DRMRightHanded"); }*/

			parseChild(pSubData);
		}
	}
}