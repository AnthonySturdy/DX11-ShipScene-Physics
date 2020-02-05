#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(GameObject* particleObject) {
}

ParticleSystem::~ParticleSystem() {
	for (int i = 0; i < particles.size(); i++) {
		delete particles[i];
	}
}

void ParticleSystem::Update(float t) {

}

void ParticleSystem::Draw() {
	for (int i = 0; i < particles.size(); i++) {

	}
}

void ParticleSystem::SetNumParticles(int amount) {
	for (int i = 0; i < particles.size(); i++) {
		delete particles[i];
	}

	for (int i = 0; i < amount; i++) {
		particles.push_back(new GameObject());
	}
}

int ParticleSystem::GetNumParticles() {
	return particles.size();
}
