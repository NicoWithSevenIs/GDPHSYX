#pragma once

#include "RenderParticle.hpp"
#include <list>
#include <functional>
#include <iomanip>

class World {
	
	public:
		std::list<RenderParticle*> particleList;
		std::vector<RenderParticle*> rankings;

	public:
		void AddParticle(RenderParticle* p);
		void Update(float deltaTime);
		void Draw();

		void printResults();
		bool allInCenter();

	private:
		void UpdateParticleList();
		std::string getRankingText(int rank);
		void printRankData(RenderParticle* p, int rank);

};