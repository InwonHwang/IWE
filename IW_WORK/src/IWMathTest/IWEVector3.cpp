#include "IWEVector3.h"



IWEVector3::IWEVector3(const IWEVector3& value)
{
	x = value.x;
	y = value.y;
	z = value.z;
}
IWEVector3::IWEVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

IWEVector3& IWEVector3::operator += (const IWEVector3& value)
{
	this->x += value.x;
	this->y += value.y;
	this->z += value.z;
	return *this;	
}
IWEVector3& IWEVector3::operator -= (const IWEVector3& value)
{
	this->x -= value.x;
	this->y -= value.y;
	this->z -= value.z;
	return *this;
}
IWEVector3& IWEVector3::operator *= (float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}
IWEVector3& IWEVector3::operator /= (float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return *this;
}

IWEVector3 IWEVector3::operator + (const IWEVector3& value) const
{
	return IWEVector3(x + value.x, y + value.y, z + value.z);
}
IWEVector3 IWEVector3::operator - (const IWEVector3& value) const
{
	return IWEVector3(x - value.x, y - value.y, z - value.z);
}
IWEVector3 IWEVector3::operator * (float value) const
{
	return IWEVector3(x * value, y * value, z * value);
}
IWEVector3 IWEVector3::operator / (float value) const
{
	return IWEVector3(x / value, y / value, z / value);
}

bool IWEVector3::operator == (const IWEVector3& value) const
{
	return (this == &value) ? true : false;
}
bool IWEVector3::operator != (const IWEVector3& value) const
{
	return (this == &value) ? false : true;
}
