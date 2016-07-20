#include "XFileMgr.h"
#include <rmxfguid.h>
#include <rmxftmpl.h>


CXFileMgr::CXFileMgr()	
{
	

}

CXFileMgr::~CXFileMgr()
{
	
}

void CXFileMgr::clear()
{
	SAFE_RELEASE(_pEnum);
	SAFE_RELEASE(_pXFile);
}

void CXFileMgr::test()
{	
	HRESULT hr;
	hr = D3DXFileCreate(&_pXFile);
	
	if (hr != S_OK)
	{
		DebugBox(hr, "D3DXFileCreate");
		return;
	}

	//템플릿 등록
	hr = _pXFile->RegisterTemplates((LPVOID)D3DRM_XTEMPLATES, D3DRM_XTEMPLATE_BYTES);
	if (hr != S_OK)
	{
		DebugBox(hr, "RegisterTemplates");
		SAFE_RELEASE(_pXFile);
		return;
	}

	//EnumObject 생성
	hr = _pXFile->CreateEnumObject((LPVOID)"../../media/mesh/tiny.x", D3DXF_FILELOAD_FROMFILE, &_pEnum);
	//hr = _pXFile->CreateEnumObject((LPVOID)"../../media/mesh/tiger.x", D3DXF_FILELOAD_FROMFILE, &_pEnum);
	if (hr != S_OK)
	{
		if(hr == S_FALSE)
		DebugBox(hr, "CreateEnumObject");
		SAFE_RELEASE(_pXFile);
		return;
	}
	
	//EnumObject 자식 개수 알아내기
	SIZE_T childCount;		
	hr = _pEnum->GetChildren(&childCount);
	if (hr != S_OK)
	{
		DebugBox(hr, "GetChildren");
		SAFE_RELEASE(_pEnum);
		SAFE_RELEASE(_pXFile);
		return;
	}
	
	DebugBox(childCount, "child Count");
	//자식 오브젝트의 템플릿 아이디 알아내기
	for (SIZE_T i = 0; i < childCount; i++)
	{
		ID3DXFileData * pData = NULL;
		hr = _pEnum->GetChild(i, &pData);
		if (hr != S_OK)
		{
			DebugBox(hr, "GetChild");
			break;
		}

		GUID guid;
		hr = pData->GetType(&guid);
		if (hr == S_OK)
		{
			if (TID_D3DRMInfo == guid) { DebugBox(0, "TID_D3DRMInfo"); }

			if (TID_D3DRMMesh == guid) { DebugBox(0, "TID_D3DRMMesh"); 

				SIZE_T sss;
				LPD3DXMESHDATA mesh = NULL;
				
				pData->Lock(&sss, (LPCVOID *)&mesh);
				if (mesh)
					DebugBox(sss, "ok");

				pData->Unlock();
			}

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

			if (TID_D3DRMAnimationSet == guid) {
				DebugBox(0, "TID_D3DRMAnimationSet");

				LPD3DXANIMATIONSET set = NULL;

				SIZE_T s = 10;
				pData->Lock(&s, (LPCVOID *)&set);
				
				if (set);
					DebugBox(s, "set OK");

				pData->Unlock();

				SIZE_T size;
				hr = pData->GetName(NULL, &size);
				char *name = new char[size];
				hr = pData->GetName(name, &size);

				if (hr == S_OK) {
					DebugBox(size, name);
					delete[] name;
				}
				else
					DebugBox(size, "??");

				SIZE_T count;
				pData->GetChildren(&count);

				for (int j = 0; j < 1; j++)
				{
					ID3DXFileData * pSubData = NULL;
					if (FAILED(pData->GetChild(j, &pSubData))) break;
					
					pSubData->Release();
				}
			}

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
		
		DebugBox(i, "i");

		SAFE_RELEASE(pData);
	}	
}
