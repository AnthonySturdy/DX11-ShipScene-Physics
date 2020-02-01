#include "ParticleModel.h"

ParticleModel::ParticleModel() {
	velocity = XMFLOAT3();
	acceleration = XMFLOAT3();
}

ParticleModel::ParticleModel(XMFLOAT3 initVelocity, XMFLOAT3 initAcceleration) {
	velocity = initVelocity;
	acceleration = initAcceleration;
}

void ParticleModel::MoveConstVelocity(const float deltaTime, Transform* curPosition) {
	curPosition->SetPosition(XMFLOAT3(curPosition->GetPosition().x + (velocity.x * deltaTime), curPosition->GetPosition().y + (velocity.y * deltaTime), curPosition->GetPosition().z + (velocity.z * deltaTime)));
}

void ParticleModel::MoveConstAcceleration(const float deltaTime, Transform* curPosition) {
	curPosition->SetPosition(XMFLOAT3(curPosition->GetPosition().x + velocity.x * deltaTime + 0.5f * acceleration.x * 0.5 * 0.5,
									curPosition->GetPosition().y + velocity.y * deltaTime + 0.5f * acceleration.y * 0.5 * 0.5,
									curPosition->GetPosition().z + velocity.z * deltaTime + 0.5f * acceleration.z * 0.5 * 0.5));

	velocity = XMFLOAT3(velocity.x + acceleration.x * deltaTime, velocity.y + acceleration.y * deltaTime, velocity.z + acceleration.z * deltaTime);
}

void ParticleModel::MoveForward(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.z += 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::MoveBackward(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.z -= 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::MoveLeft(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.x -= 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::MoveRight(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.x += 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::MoveUp(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.y += 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::MoveDown(Transform* curPosition) {
	XMFLOAT3 p = curPosition->GetPosition();
	p.y -= 0.1f;
	curPosition->SetPosition(p);
}

void ParticleModel::Update(float t) {

}
