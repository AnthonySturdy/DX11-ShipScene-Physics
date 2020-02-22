#include "ParticleModel.h"

ParticleModel::ParticleModel() {
	velocity = XMFLOAT3();
	acceleration = XMFLOAT3();
	netForce = XMFLOAT3();

	transform = nullptr;

	mass = 1.0f;
	forces.thrust = XMFLOAT3();
	forces.gravity = XMFLOAT3();
	forces.friction = XMFLOAT3(1, 1, 1);
}

ParticleModel::ParticleModel(XMFLOAT3 initVelocity, XMFLOAT3 initAcceleration) {
	velocity = initVelocity;
	acceleration = initAcceleration;
	netForce = XMFLOAT3();

	transform = nullptr;

	mass = 1.0f;
	forces.thrust = XMFLOAT3();
	forces.friction = XMFLOAT3(1, 1, 1);
	forces.gravity = XMFLOAT3();
}

void ParticleModel::MoveConstVelocity(const float deltaTime) {
	transform->SetPosition(XMFLOAT3(transform->GetPosition().x + (velocity.x * deltaTime), transform->GetPosition().y + (velocity.y * deltaTime), transform->GetPosition().z + (velocity.z * deltaTime)));
}

void ParticleModel::MoveConstAcceleration(const float deltaTime) {
	//Update position
	transform->SetPosition(XMFLOAT3(transform->GetPosition().x + (velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime), 
									transform->GetPosition().y + (velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime), 
									transform->GetPosition().z + (velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime)));

	//Apply acceleration to velocity
	velocity = XMFLOAT3(velocity.x + (acceleration.x * deltaTime), velocity.y + (acceleration.y * deltaTime), velocity.z + (acceleration.z * deltaTime));

	velocity.x *= forces.friction.x;
	velocity.y *= forces.friction.y;
	velocity.z *= forces.friction.z;
}

void ParticleModel::Update(float t) {
	UpdateNetForce();
	UpdateAcceleration();
	MoveConstAcceleration(t);

	//if (transform->GetPosition().y <= 0.5f)
		//transform->SetPosition(XMFLOAT3(transform->GetPosition().x, 0.5f, transform->GetPosition().z));

#if 0
	Debug::Print("\n");
	Debug::Print("Pos: " + std::to_string(transform->GetPosition().x) + ", " + std::to_string(transform->GetPosition().y) + ", " + std::to_string(transform->GetPosition().z) + "\n");
	Debug::Print("Net: " + std::to_string(netForce.x) + ", " + std::to_string(netForce.y) + ", " + std::to_string(netForce.z) + "\n");
	Debug::Print("Acc: " + std::to_string(acceleration.x) + ", " + std::to_string(acceleration.y) + ", " + std::to_string(acceleration.z) + "\n");
	Debug::Print("Vel: " + std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + ", " + std::to_string(velocity.z) + "\n");
	Debug::Print("Thr: " + std::to_string(forces.thrust.x) + ", " + std::to_string(forces.thrust.y) + ", " + std::to_string(forces.thrust.z) + "\n");
	Debug::Print("Fri: " + std::to_string(forces.friction.x) + ", " + std::to_string(forces.friction.y) + ", " + std::to_string(forces.friction.z) + "\n");
#endif
}

void ParticleModel::UpdateNetForce() {
	//Add thrust
	netForce.x += forces.thrust.x;
	netForce.y += forces.thrust.y;
	netForce.z += forces.thrust.z;

	//Add gravity
	netForce.x += forces.gravity.x;
	netForce.y += forces.gravity.y;
	netForce.z += forces.gravity.z;

	//Multiply by friction (1 = no friction, 0 = infinity friction)
	netForce.x *= forces.friction.x;
	netForce.y *= forces.friction.y;
	netForce.z *= forces.friction.z;
}

void ParticleModel::UpdateAcceleration() {
	acceleration = XMFLOAT3(netForce.x / mass, 
							netForce.y / mass,
							netForce.z / mass);
}
