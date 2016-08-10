#include "IWEVector3.h"

void IWEVector3::set(float x, float y, float z)
{
	_d3dxVector3.x = x;
	_d3dxVector3.y = y;
	_d3dxVector3.z = z;
}

IWEVector3::IWEVector3(D3DXVECTOR3 d3dxVector3)
	: _d3dxVector3(d3dxVector3)
{
}
IWEVector3::IWEVector3(const IWEVector3& value)
	: _d3dxVector3(value._d3dxVector3)
{		
}

IWEVector3::IWEVector3(float x, float y, float z)
	:_d3dxVector3(x, y, z)
{
}

IWEVector3& IWEVector3::operator += (const IWEVector3& value)
{
	this->_d3dxVector3 += value._d3dxVector3;	
	return *this;	
}
IWEVector3& IWEVector3::operator -= (const IWEVector3& value)
{
	this->_d3dxVector3 -= value._d3dxVector3;
	
	return *this;
}
IWEVector3& IWEVector3::operator *= (float value)
{
	this->_d3dxVector3 *= value;
	
	return *this;
}
IWEVector3& IWEVector3::operator /= (float value)
{
	this->_d3dxVector3 /= value;	
	return *this;
}

IWEVector3 IWEVector3::operator + (const IWEVector3& value) const
{
	return IWEVector3(_d3dxVector3 + value._d3dxVector3);
}
IWEVector3 IWEVector3::operator - (const IWEVector3& value) const
{
	return IWEVector3(_d3dxVector3 - value._d3dxVector3);
}
IWEVector3 IWEVector3::operator * (float value) const
{
	return IWEVector3(_d3dxVector3 * value);
}
IWEVector3 IWEVector3::operator / (float value) const
{
	return IWEVector3(_d3dxVector3 / value);
}

bool IWEVector3::operator == (const IWEVector3& value) const
{
	return (this == &value) ? true : false;
}
bool IWEVector3::operator != (const IWEVector3& value) const
{
	return (this == &value) ? false : true;
}

// 나중에 컴파일러가 찾을 수 있도록 하기
IWEVector3 operator*(float value, const IWEVector3& vector3)
{
	return (vector3 * value);
}
IWEVector3 operator/(float value, const IWEVector3& vector3)
{
	return (vector3 / value);
}

//static
const IWEVector3 IWEVector3::forward = IWEVector3(0, 0, 1);
const IWEVector3 IWEVector3::back = IWEVector3(0, 0, -1);
const IWEVector3 IWEVector3::down = IWEVector3(0, -1, 0);
const IWEVector3 IWEVector3::up = IWEVector3(0, 1, 0);
const IWEVector3 IWEVector3::right = IWEVector3(1, 0, 0);
const IWEVector3 IWEVector3::left = IWEVector3(-1, 0, 0);
const IWEVector3 IWEVector3::zero = IWEVector3(0, 0, 0);
const IWEVector3 IWEVector3::one = IWeVector3(1, 1, 1);

