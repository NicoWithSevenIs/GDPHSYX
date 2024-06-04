
#include "Particle.hpp"

void Particle::UpdatePosition(float deltaTime) {
	this->position += (velocity * deltaTime) + ( (this->acceleration * deltaTime * deltaTime) * 0.5f );
}

void Particle::UpdateVelocity(float deltaTime) {
	this->velocity += this->acceleration * deltaTime;
}

void Particle::Update(float deltaTime) {
	this->UpdatePosition(deltaTime);
	this->UpdateVelocity(deltaTime);
}

void Particle::setPosition(Vector3 position) {
	this->position = position;
}

void Particle::setVelocity(Vector3 velocity) {
	this->velocity = velocity;
	this->initialVelocity = velocity;
}

void Particle::setAcceleration(Vector3 acceleration) {
	this->acceleration = acceleration;
}

Vector3 Particle::getPosition() {
	return this->position;
}

Vector3 Particle::getVelocity() {
	return this->velocity;
}

Vector3 Particle::getInitialVelocity() {
	return this->initialVelocity;
}

void Particle::Destroy() {
	this->isDestroyed = true;
}

bool Particle::IsDestroyed() {
	return this->isDestroyed;
}