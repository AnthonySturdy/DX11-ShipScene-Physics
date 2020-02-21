#pragma once
#include <string>
#include <directxmath.h>
#include <d3d11_1.h>
#include "Structures.h"
#include "OBJLoader.h"

using namespace DirectX;

class Appearance {
private:
	Mesh _mesh;
	Material _material;

public:
	Appearance();

	Mesh* GetMesh() { return &_mesh; }
	Material* GetMaterial() { return &_material; }

	void LoadMesh(std::string dir, ID3D11Device* pd3dDevice) { _mesh = OBJLoader::Load(const_cast<char*>(dir.c_str()), pd3dDevice, false); }
	void SetMesh(Mesh mesh) { _mesh = mesh; }
	void SetMaterial(Material m) { _material = m; }
};