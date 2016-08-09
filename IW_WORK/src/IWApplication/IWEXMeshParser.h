#pragma once
#include "XParser.h"

class Mesh;

class XMeshParser final : public XParser
{
private:
	std::unique_ptr<Mesh> _mesh;

protected:
	bool parse(LPD3DXFILEDATA pXFileData, void ** ppData) override;
	bool parseSub(LPD3DXFILEDATA pXFileData, void ** ppData) override;

public:
	XMeshParser();
	~XMeshParser();

	Mesh * getData(LPD3DXFILEDATA pXFileData, void ** ppData);
};

