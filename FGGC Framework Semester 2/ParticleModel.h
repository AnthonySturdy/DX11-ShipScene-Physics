#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Transform.h"

using namespace DirectX;

class ParticleModel {
private:
	XMFLOAT3 velocity;
	XMFLOAT3 acceleration;

public:
	ParticleModel();
	ParticleModel(XMFLOAT3 initVelocity);

	XMFLOAT3 GetVelocity() { return velocity; }
	void SetVelocity(XMFLOAT3 newVelocity) { velocity = newVelocity; }
	void SetVelocity(float x, float y, float z) { velocity.x = x; velocity.y = y; velocity.z = z; }

	XMFLOAT3 GetAcceleration() { return acceleration; }
	void SetAcceleration(XMFLOAT3 newAcceleration) { acceleration = newAcceleration; }
	void SetAcceleration(float x, float y, float z) { acceleration.x = x; acceleration.y = y; acceleration.z = z; }

	void MoveConstVelocity(const float deltaTime, Transform* curPosition);
	void MoveConstAcceleration(const float deltaTime, Transform* curPosition);
	void MoveForward(Transform* curPosition);
	void MoveBackward(Transform* curPosition);
	void MoveLeft(Transform* curPosition);
	void MoveRight(Transform* curPosition);
	void MoveUp(Transform* curPosition);
	void MoveDown(Transform* curPosition);

	void Update(float t);
};