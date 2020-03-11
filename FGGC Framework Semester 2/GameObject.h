#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Structures.h"
#include "Debug.h"
#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"
#include "Rigidbody.h"

using namespace DirectX;

class GameObject
{
public:
	GameObject(std::string modelDirectory, Material material, ID3D11Device* _pd3dDevice);
	GameObject(Mesh mesh, Material material, ID3D11Device* _pd3dDevice);
	~GameObject();

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool active) { isActive = active; }
	bool GetIsStatic() { return isStatic; }
	void SetIsStatic(bool isstatic) { isStatic = isstatic; }

	Transform* GetTransform() { return &_transform; }
	Appearance* GetAppearance() { return &_appearance; }
	ParticleModel* GetParticleModel() { return &_particleModel; }
	Rigidbody* GetRigidBody() { return &_rigidbody; }

	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView* GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void SetShaderType(ShaderType st) { shaderType = st; }
	ShaderType GetShaderType() { return shaderType; }

	void SetParent(GameObject* parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

private:
	ID3D11Device* pd3dDevice;

	Transform _transform;
	Appearance _appearance;
	ParticleModel _particleModel;
	Rigidbody _rigidbody;
	ShaderType shaderType;

	bool isActive = true;
	bool isStatic = true;

	ID3D11ShaderResourceView* _textureRV;

	GameObject* _parent;
};

