#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(GameObject* particleObject, ParticleInfo info, int _numParticles, ID3D11Device* _pd3dDevice) {
	pd3dDevice = _pd3dDevice;

	numParticles = _numParticles;

	srand(time(NULL));

	for (int i = 0; i < numParticles; i++) {
		particles.push_back(std::make_pair(new GameObject(*particleObject->GetAppearance()->GetMesh(), *particleObject->GetAppearance()->GetMaterial(), pd3dDevice), info));
		particles[i].first->SetIsActive(false);
	}
}

ParticleSystem::~ParticleSystem() {
	for (auto p : particles) {
		delete p.first;
	}
}

void ParticleSystem::Update(float t) {
	for (auto& p : particles) {
		p.first->Update(t);	//Update particle gameobject

		//Subtract time from particle life, deactivate if below 0
		if (p.first->GetIsActive())
			p.second.lifeTimeRemaining -= t;

		if (p.second.lifeTimeRemaining <= 0.0f) {
			p.first->SetIsActive(false);
		}
	}
}

void ParticleSystem::Draw(ID3D11DeviceContext* pImmediateContext, ID3D11Buffer* constantBuffer, ConstantBuffer cb) {
	for (auto& p : particles) {
		cb.World = XMMatrixTranspose(p.first->GetTransform()->GetWorldMatrix());
		pImmediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, 0, 0);

		p.first->Draw(pImmediateContext);
	}
}

void ParticleSystem::Emit() {
	Emit(particles[curParticleIndex].second);
}

void ParticleSystem::Emit(ParticleInfo info) {
	//Set to active and set lifetime
	particles[curParticleIndex].second.lifeTimeRemaining = particles[curParticleIndex].second.lifeTime;
	int random1 = (rand() % 51) - 25;
	int random2 = (rand() % 51) - 25;

	particles[curParticleIndex].second.initVelocity.x += random1;
	particles[curParticleIndex].second.initVelocity.z += random2;

	//Set object physics properties
	particles[curParticleIndex].first->GetParticleModel()->SetThrust(particles[curParticleIndex].second.thrust);
	particles[curParticleIndex].first->GetParticleModel()->SetFriction(particles[curParticleIndex].second.friction);
	particles[curParticleIndex].first->GetParticleModel()->SetGravity(particles[curParticleIndex].second.gravity);
	particles[curParticleIndex].first->GetParticleModel()->SetVelocity(particles[curParticleIndex].second.initVelocity);
	particles[curParticleIndex].first->GetParticleModel()->SetAcceleration(XMFLOAT3());
	particles[curParticleIndex].first->GetParticleModel()->SetNetforce(XMFLOAT3());

	particles[curParticleIndex].first->GetTransform()->SetPosition(info.position);
	particles[curParticleIndex].first->GetTransform()->SetScale(info.scale);

	particles[curParticleIndex].first->SetIsActive(true);

	//Increase particle index, if more than max particles, reset to 0
	curParticleIndex++;
	if (curParticleIndex == numParticles)
		curParticleIndex = 0;
}

void ParticleSystem::SetParticleInfo(ParticleInfo info) {
	//Change ParticleInfo on all particles
	for (auto p : particles) {
		p.second = info;
	}
}