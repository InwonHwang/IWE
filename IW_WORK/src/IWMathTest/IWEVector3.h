#pragma once
class IWEVector3
{
	float x;
	float y;
	float z;
public:
	IWEVector3() {};
	IWEVector3(const IWEVector3&);
	IWEVector3(float x, float y, float z);
	~IWEVector3() {}


	// assignment operators
	IWEVector3& operator += (const IWEVector3&);
	IWEVector3& operator -= (const IWEVector3&);
	IWEVector3& operator *= (float);
	IWEVector3& operator /= (float);

	// binary operators
	IWEVector3 operator + (const IWEVector3&) const;
	IWEVector3 operator - (const IWEVector3&) const;
	IWEVector3 operator * (float) const;
	IWEVector3 operator / (float) const;
	bool operator == (const IWEVector3&) const;
	bool operator != (const IWEVector3&) const;
};

