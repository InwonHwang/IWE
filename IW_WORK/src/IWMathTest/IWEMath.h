#pragma once
#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>



using namespace std;



static class IWEMath
{	
	

private:
	IWEMath() {}
	

public:
	static float Infinity(){ return INFINITY; }
	static float RadToDeg() { return (M_PI / 180); }
	static float DegToRad() { return (180 / M_PI); }

public:
	static int Abs(int);
	static float Abs(float);

	static float Acos(float);
	static float Asin(float);
	static float Atan(float);
	static float Atan2(float, float);

	static float Sin(float);
	static float Cos(float);
	static float Tan(float);

	static float Sqrt(float);
	static float Log(float);
	static float Log10(float);

	static float Round(float);
	static int RountToInt(float);

	static float Exp(float);
	static float Floor(float);
	static int FloorToInt(float);

	static float Ceil(float);
	static int CeilToInt(float);
	static float Clamp(float, float, float);
};

