#pragma once
#include <directxmath.h>
#include <d3d11_1.h>

using namespace DirectX;

struct Mesh {
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT VBStride;
	UINT VBOffset;
	UINT IndexCount;
};

struct Material {
	Material() {
		diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		specularPower = 10.0f;
	}

	Material(XMFLOAT4 d, XMFLOAT4 a, XMFLOAT4 s, float sp) {
		diffuse = d;
		ambient = a;
		specular = s;
		specularPower = sp;
	}

	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexC;

	bool operator<(const SimpleVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	};
};

struct SurfaceInfo
{
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 SpecularMtrl;
};

struct Light
{
	XMFLOAT4 AmbientLight;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 SpecularLight;

	float SpecularPower;
	XMFLOAT3 LightVecW;
};

struct ConstantBuffer
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	SurfaceInfo surface;

	Light light;

	XMFLOAT3 EyePosW;
	float HasTexture;
};

enum ShaderType {
	UNDEFINED = 0,
	DEFAULT,
	BOAT,
	WATER,
	LAND_UNDER_WATER,
	NO_LIGHT,
};