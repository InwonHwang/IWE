#pragma once
#include "stdafx.h"

class IWEVector3
{
	friend class Transform;
	friend class IWEQuaternion;
private:
	D3DXVECTOR3 _d3dxVector3;
	IWEVector3(D3DXVECTOR3);

public:
	float x() { return _d3dxVector3.x; }
	float y() { return _d3dxVector3.y; }
	float z() { return _d3dxVector3.z; }

	void set(float, float, float);


public:
	IWEVector3() : _d3dxVector3(0, 0, 0) {}
	IWEVector3(const IWEVector3&);
	IWEVector3(float x, float y, float z);
	~IWEVector3() {}

	IWEVector3& operator += (const IWEVector3&);
	IWEVector3& operator -= (const IWEVector3&);
	IWEVector3& operator *= (float);
	IWEVector3& operator /= (float);

	IWEVector3 operator + (const IWEVector3&) const;
	IWEVector3 operator - (const IWEVector3&) const;
	IWEVector3 operator * (float) const;
	IWEVector3 operator / (float) const;
	bool operator == (const IWEVector3&) const;
	bool operator != (const IWEVector3&) const;

	friend IWEVector3 operator*(float, const IWEVector3&);
	friend IWEVector3 operator/(float, const IWEVector3&);

public:
	static const IWEVector3 forward;
	static const IWEVector3 back;
	static const IWEVector3 down;
	static const IWEVector3 up;
	static const IWEVector3 right;
	static const IWEVector3 left;
	static const IWEVector3 zero;
	
};


