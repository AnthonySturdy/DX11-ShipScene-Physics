#include "ParticleModel.h"

ParticleModel::ParticleModel() {
	velocity = XMFLOAT3();
}

ParticleModel::ParticleModel(XMFLOAT3 initVelocity) {
	velocity = initVelocity;
}

XMFLOAT3 ParticleModel::MoveConstVelocity(const float deltaTime, XMFLOAT3 curPosition) {
	return XMFLOAT3(curPosition.x + (velocity.x * deltaTime), curPosition.y + (velocity.y * deltaTime), curPosition.z + (velocity.z * deltaTime));
}

XMFLOAT3 ParticleModel::MoveForward(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.z -= 0.1f;
	return returnVar;
}

XMFLOAT3 ParticleModel::MoveLeft(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.x -= 0.1f;
	return returnVar;
}

XMFLOAT3 ParticleModel::MoveRight(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.x += 0.1f;
	return returnVar;
}

XMFLOAT3 ParticleModel::MoveBackward(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.z += 0.1f;
	return returnVar;
}

XMFLOAT3 ParticleModel::MoveUp(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.y += 0.1f;
	return returnVar;
}

XMFLOAT3 ParticleModel::MoveDown(XMFLOAT3 curPosition) {
	XMFLOAT3 returnVar = curPosition;
	returnVar.y -= 0.1f;
	return returnVar;
}

void ParticleModel::Update(float t) {

}
