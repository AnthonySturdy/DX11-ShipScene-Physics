#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "ParticleModel.h"
#include "Quaternion.h"
#include "vector3.h"
#include "Debug.h"

using namespace DirectX;

class Rigidbody {
private:
	ParticleModel* particleModel;
	Quaternion quaternion;

	XMMATRIX inertiaTensor;
	XMFLOAT3 curForceDir = XMFLOAT3(), curPointForceApplied = XMFLOAT3();

	XMVECTOR torque = XMVECTOR();
	XMVECTOR angularAcceleration = XMVECTOR();
	XMVECTOR angularVelocity = XMVECTOR();
	float angularDamping = 0.93f;
	XMMATRIX angularOrientation = XMMATRIX();

	XMVECTOR CalculateTorque(XMFLOAT3 forceDirection, XMFLOAT3 pointForceApplied);	//A direction of the force, and a point relative to the centre of mass which it's applied
	XMMATRIX CalculateInertiaTensor(float w, float h, float d);	//Calculated for a rectangular prism
	XMVECTOR CalculateAngularAcceleration();
	XMVECTOR CalculateAngularVelocity(float deltaTime);
	XMVECTOR ApplyDamping(float deltaTime);
	XMMATRIX CalculateAngularOrientation(XMFLOAT3 position, float deltaTime);

public:
	Rigidbody();
	Rigidbody(float w, float h, float d, ParticleModel* pm);	//TODO: Add another for sphere inertia tensor? This will only work for rectangular prism inertia tensor

	void Update(float deltaTime);

	XMMATRIX* GetAngularOrientation();
	void SetAngularDamping(float d) { angularDamping = d; }

	void ApplyForce(XMFLOAT3 forceDir, XMFLOAT3 pointForceApplied) { curForceDir = forceDir; curPointForceApplied = pointForceApplied; }
};