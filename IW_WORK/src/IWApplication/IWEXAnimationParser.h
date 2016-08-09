#pragma once
#include "XParser.h"

class Animation;

class XAnimationParser final : public XParser
{
private:
	std::unique_ptr<Animation> _animation;

	void loadAnimationKey(LPD3DXFILEDATA pXFileData, void ** ppData);
	void loadAnimationOptions(LPD3DXFILEDATA pXFileData, void ** ppData);
	void loadBoneName(LPD3DXFILEDATA pXFileData, void ** ppData);	

protected:
	bool parse(LPD3DXFILEDATA pXFileData, void ** ppData) override;
	bool parseSub(LPD3DXFILEDATA pXFileData, void ** ppData) override;	

public:
	XAnimationParser();
	~XAnimationParser();

	Animation * getData(LPD3DXFILEDATA pXFileData, void ** ppData);
	
};

