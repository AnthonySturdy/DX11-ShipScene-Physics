#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Transform.h"
#include "Debug.h"

using namespace DirectX;

struct Forces {
	XMFLOAT3 thrust;
	XMFLOAT3 friction;
	XMFLOAT3 gravity;
};

class ParticleModel {
private:
	XMFLOAT3 velocity;		//Velocity is the final direction which is applied to the position
	XMFLOAT3 acceleration;	//Acceleration is the forces being applied, then mass applied to that
	XMFLOAT3 netForce;		//Net force is all forces being applied to object

	Transform* transform;

	float mass;
	Forces forces;

public:
	ParticleModel();
	ParticleModel(XMFLOAT3 initVelocity, XMFLOAT3 initAcceleration);

	XMFLOAT3 GetVelocity() { return velocity; }
	void SetVelocity(XMFLOAT3 newVelocity) { velocity = newVelocity; }
	void SetVelocity(float x, float y, float z) { velocity.x = x; velocity.y = y; velocity.z = z; }

	XMFLOAT3 GetAcceleration() { return acceleration; }
	void SetAcceleration(XMFLOAT3 newAcceleration) { acceleration = newAcceleration; }
	void SetAcceleration(float x, float y, float z) { acceleration.x = x; acceleration.y = y; acceleration.z = z; }

	XMFLOAT3 GetNetforce() { return netForce; }
	void SetNetforce(XMFLOAT3 newNetForce) { netForce = newNetForce; }
	void SetNetforce(float x, float y, float z) { netForce.x = x; netForce.y = y; netForce.z = z; }

	Transform* GetTransform() { return transform; }
	void SetTransform(Transform* t) { transform = t; }

	int GetMass() { return mass; }
	void SetMass(int m) { mass = m; }
	void SetThrust(XMFLOAT3 t) { forces.thrust = t; }
	void SetFriction(XMFLOAT3 f) { forces.friction = f; }
	void SetGravity(XMFLOAT3 g) { forces.gravity = g; }

	void MoveConstVelocity(const float deltaTime);
	void MoveConstAcceleration(const float deltaTime);

	void Update(float t);
	void UpdateNetForce();
	void UpdateAcceleration();
};