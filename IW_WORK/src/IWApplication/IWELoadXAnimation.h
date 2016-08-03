#pragma once
#include "ILoadXFile.h"

class Animation;

class LoadXAnimation final : public ILoadXFile
{
private:
	std::unique_ptr<Animation> _animation;

public:
	LoadXAnimation();
	~LoadXAnimation();

	Animation * getData();
	bool loadData(LPD3DXFILEDATA pXFileData, void ** ppData) override;
};

