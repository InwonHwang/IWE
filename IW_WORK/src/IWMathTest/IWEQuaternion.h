#pragma once
#include "stdafx.h"

class IWEQuaternion
{
	friend class Transform;
private:
	D3DXQUATERNION _d3dxQuaternion;
	IWEQuaternion(D3DXQUATERNION);

public:	
	float x() { return _d3dxQuaternion.x; }
	float y() { return _d3dxQuaternion.y; }
	float z() { return _d3dxQuaternion.z; }
	float w() { return _d3dxQuaternion.w; }

	void set(float, float, float, float);

public:
	IWEQuaternion() : _d3dxQuaternion(0, 0 ,0, 0) {}
	IWEQuaternion(const IWEQuaternion&);
	IWEQuaternion(float x, float y, float z, float w);
	~IWEQuaternion() {}


	IWEQuaternion& operator += (const IWEQuaternion&);
	IWEQuaternion& operator -= (const IWEQuaternion&);
	IWEQuaternion& operator *= (float);
	IWEQuaternion& operator /= (float);

	IWEQuaternion operator + (const IWEQuaternion&) const;
	IWEQuaternion operator - (const IWEQuaternion&) const;
	IWEQuaternion operator * (float) const;
	IWEQuaternion operator / (float) const;
	bool operator == (const IWEQuaternion&) const;
	bool operator != (const IWEQuaternion&) const;

	friend IWEQuaternion operator*(float, const IWEQuaternion&);
	friend IWEQuaternion operator/(float, const IWEQuaternion&);
public:
	static const IWEQuaternion identity;

public:
	static float Angle(const IWEQuaternion&, const IWEQuaternion&);
	static IWEQuaternion Euler(float x, float y, float z);
	static IWEQuaternion AngleAxis(float, const IWEVector3&);
	static IWEQuaternion Inverse(const IWEQuaternion&);
	static IWEQuaternion SLerp(const IWEQuaternion&, const IWEQuaternion&, float);
	
};

