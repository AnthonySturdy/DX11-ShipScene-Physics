#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Structures.h"

using namespace DirectX;

class Appearance {
private:
	Mesh _mesh;
	Material _material;

public:
	Appearance();

	Mesh* GetMesh() { return &_mesh; }
	Material* GetMaterial() { return &_material; }

	void SetMesh(Mesh m) { _mesh = m; }
	void SetMaterial(Material m) { _material = m; }
};