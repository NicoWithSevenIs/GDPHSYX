#include "World.hpp"


void World::Update(float deltaTime) {
	this->UpdateParticleList();
	for (auto p : particleList) 
		p->Update(deltaTime);
}

void World::AddParticle(Particle* p) {
	this->particleList.push_back(p);
}

void World::UpdateParticleList() {

	auto removeCheck = [](Particle* p) {
		return p->IsDestroyed();
	};

	this->particleList.remove_if(removeCheck);


}