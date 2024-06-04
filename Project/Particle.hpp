#pragma once

#include "Vector3.hpp"
class Particle {
	
	private:
		float mass = 0;
		bool isDestroyed = false;

	private:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

		Vector3 initialVelocity;

	protected:
		void UpdatePosition(float deltaTime);
		void UpdateVelocity(float deltaTime);

	public:
		void Update(float deltaTime);
		void Destroy();
		bool IsDestroyed();

	public: 
		void setPosition(Vector3 position);
		void setVelocity(Vector3 velocity);
		void setAcceleration(Vector3 acceleration);

	public:
		Vector3 getPosition();
		Vector3 getVelocity();
		Vector3 getInitialVelocity();
};