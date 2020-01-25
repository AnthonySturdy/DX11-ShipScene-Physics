#pragma once
#include <directxmath.h>
#include <d3d11_1.h>

using namespace DirectX;

//TODO: Implement Acceleration (Week 1, Tutorial 3)

class ParticleModel {
private:
	XMFLOAT3 velocity;

public:
	ParticleModel();
	ParticleModel(XMFLOAT3 initVelocity);

	XMFLOAT3 GetVelocity() { return velocity; }
	void SetVelocity(XMFLOAT3 newVelocity) { velocity = newVelocity; }
	void SetVelocity(float x, float y, float z) { velocity.x = x; velocity.y = y; velocity.z = z; }

	XMFLOAT3 MoveConstVelocity(const float deltaTime, XMFLOAT3 curPosition);
	XMFLOAT3 MoveForward(XMFLOAT3 curPosition);
	XMFLOAT3 MoveLeft(XMFLOAT3 curPosition);
	XMFLOAT3 MoveRight(XMFLOAT3 curPosition);
	XMFLOAT3 MoveBackward(XMFLOAT3 curPosition);
	XMFLOAT3 MoveUp(XMFLOAT3 curPosition);
	XMFLOAT3 MoveDown(XMFLOAT3 curPosition);

	void Update(float t);
};