#pragma once
#include "stdafx.h"
#include "IXParser.h"

class CMesh;

class CMeshParser final : public IXParser
{
private:
	std::list<CMesh *> _meshes;

private:
	void parseXFileData(ID3DXFileData* pFileData, void ** ppData) override;
	void parseXFile(char* filename, void **ppData) override;

public:
	CMeshParser() {}
	~CMeshParser() {}

	CMesh* parse(char *filename);
};