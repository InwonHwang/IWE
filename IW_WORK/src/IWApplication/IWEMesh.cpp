#include "IWEMesh.h"
#include "IWEMaterial.h"
#include "IWETransform.h"
#include "IWEGameObject.h"
#include "Device.h"

Mesh::Mesh()
	: _pMeshData(NULL),	
	_pSkinnedMeshData(NULL),
	_pEffects(NULL),
	_pSkinInfo(NULL),
	_pAdjacency(NULL),
	_materials(NULL),
	_numMaterials(0)
{
	_pMeshData = new D3DXMESHDATA();
	_pSkinnedMeshData = new D3DXMESHDATA();
}


Mesh::~Mesh()
{		
	RELEASE_COM(_pSkinInfo);	
	RELEASE_COM(_pMeshData->pMesh);
	RELEASE_COM(_pMeshData->pPatchMesh);
	RELEASE_COM(_pMeshData->pPMesh);
	RELEASE_COM(_pSkinnedMeshData->pMesh);
	RELEASE_COM(_pSkinnedMeshData->pPatchMesh);
	RELEASE_COM(_pSkinnedMeshData->pPMesh);
	SAFE_DELETE(_pMeshData);
	SAFE_DELETE(_pSkinnedMeshData);
	SAFE_DELETE(_pAdjacency);
	SAFE_DELETE_ARRAY(_materials);
}

void Mesh::findBone(Transform *rootTransform)
{
	if (!_pSkinInfo) return;
	if (!_BoneMatrices) _BoneMatrices = new LPD3DXMATRIX[_pSkinInfo->GetNumBones()];

	for (DWORD i = 0; i < _pSkinInfo->GetNumBones(); i++)
	{
		Transform* transform = Transform::findChild(rootTransform, _pSkinInfo->GetBoneName(i));

		if (transform)
		{
			_BoneMatrices[i] = &transform->_pMatrix;
		}
	}
	
}

void Mesh::update()
{
	D3DXMATRIX* matrices = NULL;

	if (_pMeshData && _pSkinInfo)
	{
		DWORD numBones = _pSkinInfo->GetNumBones();    

		matrices = new D3DXMATRIX[numBones];
		for (DWORD i = 0; i < numBones; i++)
		{
			D3DXMatrixMultiply(&matrices[i], _pSkinInfo->GetBoneOffsetMatrix(i), _BoneMatrices[i]);			
		}

		void* pSrc = NULL;    // a void pointer for the original mesh
		void* pDst = NULL;    // a void pointer for the original mesh

		_pMeshData->pMesh->LockVertexBuffer(NULL, &pSrc);
		_pSkinnedMeshData->pMesh->LockVertexBuffer(NULL, &pDst);

		_pSkinInfo->UpdateSkinnedMesh(matrices, NULL, pSrc, pDst);

		_pSkinnedMeshData->pMesh->UnlockVertexBuffer();
		_pMeshData->pMesh->UnlockVertexBuffer();

		for (DWORD i = 0; i < _numMaterials; i++)
		{
			g_Device->SetMaterial(&_materials[i]._matD3D);

			g_Device->SetTexture(0, _materials[i]._texture);

			_pMeshData->pMesh->DrawSubset(i);
		}

		SAFE_DELETE(matrices);
	}

//	if (_pSkinInfo)
//	{
//		int NumBones = _pSkinInfo->GetNumBones();
//		D3DXMATRIX* BoneMatrices = new D3DXMATRIX[NumBones];
//
//		// prepare final matrices
//		for (int i = 0; i<NumBones; i++)
//		{
//			D3DXMatrixMultiply(&BoneMatrices[i], _pSkinInfo->GetBoneOffsetMatrix(i), _BoneMatrices[i]);
//		}
//
//		// generate skinned mesh
//		_pSkinInfo->UpdateSkinnedMesh(BoneMatrices, _pSkinnedMeshData->pMesh);
//		SAFE_DELETE_ARRAY(BoneMatrices);
//
//		
//		BYTE* Points = NULL;
//		_BoneMatrices->LockVertexBufferUni(D3DLOCK_READONLY, &Points);
//		if (FAILED(res))
//		{
//			Game->LOG(res, "Error updating bounding box");
//			return res;
//		}
//
//#ifdef WME_D3D9
//		D3DXComputeBoundingBox((LPD3DXVECTOR3)Points, m_BlendedMesh->GetNumVertices(), D3DXGetFVFVertexSize(m_BlendedMesh->GetFVF()), &m_BBoxStart, &m_BBoxEnd);
//#else
//		D3DXComputeBoundingBox((void*)Points, m_BlendedMesh->GetNumVertices(), m_BlendedMesh->GetFVF(), &m_BBoxStart, &m_BBoxEnd);
//#endif
//		// if you want something done right...
//		if (_isnan(m_BBoxEnd.x))
//		{
//			float MinX = FLT_MAX;
//			float MinY = FLT_MAX;
//			float MinZ = FLT_MAX;
//			float MaxX = FLT_MIN;
//			float MaxY = FLT_MIN;
//			float MaxZ = FLT_MIN;
//
//			DWORD FvfSize = m_BlendedMesh->GetFVF();
//
//			BYTE* VectBuf = (BYTE*)Points;
//			for (int i = 0; i<m_BlendedMesh->GetNumVertices(); i++)
//			{
//				D3DXVECTOR3* Vect = (D3DXVECTOR3*)VectBuf;
//
//				MinX = min(MinX, Vect->x);
//				MinY = min(MinY, Vect->y);
//				MinZ = min(MinZ, Vect->z);
//
//				MaxX = max(MaxX, Vect->x);
//				MaxY = max(MaxY, Vect->y);
//				MaxZ = max(MaxZ, Vect->z);
//
//				VectBuf += D3DXGetFVFVertexSize(FvfSize);
//			}
//			m_BBoxStart = D3DXVECTOR3(MinX, MinY, MinZ);
//			m_BBoxEnd = D3DXVECTOR3(MaxX, MaxY, MaxZ);
//		}
//
//		m_BlendedMesh->UnlockVertexBuffer();
//	}

}