#pragma once
#include "IXParser.h"

class CSkinnedMesh;

class CSkinnedMeshParser final : public IXParser
{
private:
	std::list<CSkinnedMesh *> _skinnedMeshes;

private:
	void parseXFileData(ID3DXFileData* pFileData, void ** ppData) override;
	void parseXFile(char* filename, void **ppData) override;

public:
	CSkinnedMeshParser() {}
	~CSkinnedMeshParser() {}

	CSkinnedMesh* parse(char *filename);
};

