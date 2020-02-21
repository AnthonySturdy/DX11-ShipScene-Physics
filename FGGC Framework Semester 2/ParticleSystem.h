#pragma once
#include <time.h>
#include <vector>
#include <directxmath.h>
#include <d3d11_1.h>
#include "GameObject.h"
#include "Debug.h"

struct ParticleInfo {
	XMFLOAT3 position;
	XMFLOAT3 scale;
	XMFLOAT3 thrust;
	XMFLOAT3 friction;
	XMFLOAT3 gravity;
	XMFLOAT3 initVelocity;

	float lifeTime = 10.0f;
	float lifeTimeRemaining = 0.0f;
};

class ParticleSystem {
private:
	int numParticles;
	int curParticleIndex = 0;
	std::vector<std::pair<GameObject*, ParticleInfo>> particles;

	ID3D11Device* pd3dDevice;

public:
	ParticleSystem(GameObject* particleObject, ParticleInfo info, int _numParticles, ID3D11Device* _pd3dDevice);
	~ParticleSystem();

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext, ID3D11Buffer* constantBuffer, ConstantBuffer cb);

	void Emit();
	void Emit(ParticleInfo info);

	void SetParticleInfo(ParticleInfo info);
};