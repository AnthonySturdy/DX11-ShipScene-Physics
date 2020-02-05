#pragma once
#include <vector>
#include "GameObject.h"

class ParticleSystem {
private:

	std::vector<GameObject*> particles;

public:
	ParticleSystem(GameObject* particleObject);
	~ParticleSystem();

	void Update(float t);
	void Draw();

	void SetNumParticles(int amount);
	int GetNumParticles();

};