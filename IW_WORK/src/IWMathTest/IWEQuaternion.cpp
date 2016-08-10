#include "IWEQuaternion.h"

void IWEQuaternion::set(float x, float y, float z, float w)
{
	_d3dxQuaternion.x = x;
	_d3dxQuaternion.y = y;
	_d3dxQuaternion.z = z;
	_d3dxQuaternion.w = w;
}

IWEQuaternion::IWEQuaternion(D3DXQUATERNION value)
	: _d3dxQuaternion(value)
{	
}


IWEQuaternion::IWEQuaternion(const IWEQuaternion& value)
	: _d3dxQuaternion(value._d3dxQuaternion)
{	
}
IWEQuaternion::IWEQuaternion(float x, float y, float z, float w)
	: _d3dxQuaternion(x, y, z, w)
{}



IWEQuaternion& IWEQuaternion::operator += (const IWEQuaternion& value)
{
	this->_d3dxQuaternion += value._d3dxQuaternion;
	return *this;
}
IWEQuaternion& IWEQuaternion::operator -= (const IWEQuaternion& value)
{
	this->_d3dxQuaternion -= value._d3dxQuaternion;
	return *this;
}
IWEQuaternion& IWEQuaternion::operator *= (float value)
{
	this->_d3dxQuaternion *= value;
	return *this;
}
IWEQuaternion& IWEQuaternion::operator /= (float value)
{
	this->_d3dxQuaternion /= value;
	return *this;
}


IWEQuaternion IWEQuaternion::operator + (const IWEQuaternion& value) const
{
	return IWEQuaternion(_d3dxQuaternion + value._d3dxQuaternion);
}
IWEQuaternion IWEQuaternion::operator - (const IWEQuaternion& value) const
{
	return IWEQuaternion(_d3dxQuaternion - value._d3dxQuaternion);
}
IWEQuaternion IWEQuaternion::operator * (float value) const
{
	return IWEQuaternion(_d3dxQuaternion * value);
}
IWEQuaternion IWEQuaternion::operator / (float value) const 
{
	return IWEQuaternion(_d3dxQuaternion / value);
}
bool IWEQuaternion::operator == (const IWEQuaternion& value) const
{
	return (this == &value) ? true : false;
}
bool IWEQuaternion::operator != (const IWEQuaternion& value) const
{
	return (this == &value) ? false : true;
}

// 나중에 컴파일러가 찾을 수 있도록 하기
IWEQuaternion operator*(float value, const IWEQuaternion& quaternion)
{
	return (quaternion * value);
}
IWEQuaternion operator/(float value, const IWEQuaternion& quaternion)
{
	return (quaternion / value);
}

//static

 const IWEQuaternion IWEQuaternion::identity = IWEQuaternion(0,0,0,0);

IWEQuaternion IWEQuaternion::Euler(float x, float y, float z)
{
	IWEQuaternion ret;
	D3DXQuaternionRotationYawPitchRoll(&ret._d3dxQuaternion, y * IWEMath::DegToRad(), x * IWEMath::DegToRad(), z * IWEMath::DegToRad());
	return ret;
}

float IWEQuaternion::Angle(const IWEQuaternion& q1, const IWEQuaternion& q2)
{
	D3DXQUATERNION inv, res;
	D3DXQuaternionInverse(&inv, &q1._d3dxQuaternion);
	res = q2._d3dxQuaternion * inv;

	return IWEMath::Acos(res.w);
}

IWEQuaternion IWEQuaternion::AngleAxis(float d, const IWEVector3& v)
{
	IWEQuaternion ret;
	D3DXQuaternionRotationAxis(&ret._d3dxQuaternion, &v._d3dxVector3, d);
	return ret;
}

IWEQuaternion IWEQuaternion::Inverse(const IWEQuaternion& q)
{
	IWEQuaternion ret;
	D3DXQuaternionInverse(&ret._d3dxQuaternion, &q._d3dxQuaternion);
	return ret;
}
IWEQuaternion IWEQuaternion::SLerp(const IWEQuaternion& q1, const IWEQuaternion& q2, float m)
{
	IWEQuaternion ret;
	D3DXQuaternionSlerp(&ret._d3dxQuaternion, &q1._d3dxQuaternion, &q2._d3dxQuaternion, m);
	return ret;
}