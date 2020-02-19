#pragma once
#include <vector>
#include <directxmath.h>
#include <d3d11_1.h>
#include "GameObject.h"
#include "Debug.h"

#define PARTICLE_AMOUNT 200

struct ParticleInfo {
	XMFLOAT3 position;
	XMFLOAT3 thrust;
	XMFLOAT3 friction;

	float lifeTime = 10.0f;
	float lifeTimeRemaining = 0.0f;
};

class ParticleSystem {
private:
	int curParticleIndex = 0;
	std::vector<std::pair<GameObject*, ParticleInfo>> particles;

public:
	ParticleSystem(GameObject* particleObject, ParticleInfo info);
	~ParticleSystem();

	void Update(float t);
	void Draw(ID3D11DeviceContext* pImmediateContext);

	void Emit();
	void Emit(ParticleInfo info);

	void SetParticleInfo(ParticleInfo info);
};