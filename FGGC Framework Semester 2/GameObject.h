#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Structures.h"
#include "Debug.h"
#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"

using namespace DirectX;

class GameObject
{
public:
	GameObject(std::string modelDirectory, Material material, ID3D11Device* _pd3dDevice);
	GameObject(Mesh mesh, Material material, ID3D11Device* _pd3dDevice);
	~GameObject();

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool active) { isActive = active; }

	Transform* GetTransform() { return &_transform; }
	Appearance* GetAppearance() { return &_appearance; }
	ParticleModel* GetParticleModel() { return &_particleModel; }

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	ID3D11Device* pd3dDevice;

	Transform _transform;
	Appearance _appearance;
	ParticleModel _particleModel;

	bool isActive = true;

	ID3D11ShaderResourceView* _textureRV;

	GameObject* _parent;
};

