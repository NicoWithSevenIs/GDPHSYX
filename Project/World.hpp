#pragma once

#include "Particle.hpp"
#include <list>
#include <functional>

class World {
	
	private:
		std::list<Particle*> particleList;

	public:
		void AddParticle(Particle* p);
		void Update(float deltaTime);

	private:
		void UpdateParticleList();


};