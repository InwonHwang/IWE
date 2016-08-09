#include "IWETransform.h"
#include "IWEGameObject.h"
#include "Device.h"

Transform::Transform()
	: gameObject(NULL)
{	
	D3DXQuaternionIdentity(&rotation);
}

Transform::~Transform()
{
	
}

void Transform::update()
{	
	D3DXMATRIX tmpScale;
	D3DXMatrixScaling(&tmpScale, scale.x, scale.y, scale.z);
	/*D3DXMATRIX tmpPositon;
	D3DXMatrixTranslation(&tmpPositon , position.x, position.y, position.z);*/
	/*D3DXQuaternionRotationYawPitchRoll(&tmpQuaternion, rotation.y, rotation.x, rotation.z);
	D3DXMatrixRotationQuaternion(&tmpRotation, &tmpQuaternion);*/
	/*D3DXMATRIX tmpRotation;
	D3DXQUATERNION tmpQuaternion;
	D3DXQuaternionRotationYawPitchRoll(&tmpQuaternion, rotation.y, rotation.x, rotation.z);
	D3DXMatrixRotationQuaternion(&tmpRotation, &tmpQuaternion);*/
	g_Device->SetTransform(D3DTS_WORLD, &(tmpScale));

}