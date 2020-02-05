#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(GameObject* particleObject, ParticleInfo info) {
	for (int i = 0; i < PARTICLE_AMOUNT; i++) {
		particles.push_back(std::make_pair((GameObject*)malloc(sizeof(particleObject)), info));
		//std::copy(particleObject, particleObject + sizeof(particleObject), particles[i].first);

		std::memcpy(particles[i].first, particleObject, sizeof(particleObject));	//I THINK THE PROBLEM IS WITH THIS FUCKING C++ AHH
	}
}

ParticleSystem::~ParticleSystem() {
	for (auto p : particles) {
		delete p.first;
	}
}

void ParticleSystem::Update(float t) {
	for (auto p : particles) {
		p.first->Update(t);	//Update particle gameobject

		//Subtract time from particle life, deactivate if below 0
		p.second.lifeTimeRemaining -= t;
		if (p.second.lifeTimeRemaining <= 0.0f) {
			p.first->SetIsActive(false);
		}
	}
}

void ParticleSystem::Draw(ID3D11DeviceContext* pImmediateContext) {
	for (auto p : particles) {
		p.first->Draw(pImmediateContext);
	}
}

void ParticleSystem::Emit() {
	Emit(particles[curParticleIndex].second);
}

void ParticleSystem::Emit(ParticleInfo info) {
	//Set to active and set lifetime
	particles[curParticleIndex].first->SetIsActive(true);
	particles[curParticleIndex].second.lifeTimeRemaining = particles[curParticleIndex].second.lifeTime;

	//Set object physics properties
	particles[curParticleIndex].first->GetParticleModel()->SetThrust(particles[curParticleIndex].second.thrust);
	particles[curParticleIndex].first->GetParticleModel()->SetFriction(particles[curParticleIndex].second.friction);

	particles[curParticleIndex].first->GetTransform()->SetPosition(info.position);

	//Increase particle index, if more than max particles, reset to 0
	curParticleIndex++;
	if (curParticleIndex == PARTICLE_AMOUNT)
		curParticleIndex = 0;
}

void ParticleSystem::SetParticleInfo(ParticleInfo info) {
	//Change ParticleInfo on all particles
	for (auto p : particles) {
		p.second = info;
	}
}