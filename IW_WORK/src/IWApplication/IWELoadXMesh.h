#pragma once
#include "ILoadXFile.h"

class Mesh;

class LoadXMesh final : public ILoadXFile
{
private:
	std::unique_ptr<Mesh> _mesh;

public:
	LoadXMesh();
	~LoadXMesh();

	Mesh * getData();
	bool loadData(LPD3DXFILEDATA pXFileData, void ** ppData) override;
};

