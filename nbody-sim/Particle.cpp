#include "Particle.h"



Particle::Particle()
{
	this->velocity = glm::vec2(0, 0);
}


Particle::Particle(glm::vec2 p, float mass)
{
	this->position = p;
	this->mass = mass;
	this->velocity = glm::vec2(0, 0);
}

Particle::Particle(glm::vec2 p, float mass, vec2 initialVelocity)
{
	this->velocity = glm::vec2(0, 0);
	this->position = p;
	this->mass = mass; // Mass of Object for particle gravity
	this->velocity = initialVelocity; //Initial Velocity of  Particle
}

Particle::~Particle()
{
}
/*Get the Physics class to do the calculation */
void Particle::accept(Physics physics, Particle* p2)
{
	vec2 grav = physics.calculateGravityFrom(this->position, p2->position, p2->mass); // Obtain the gravity vector
	this->velocity += grav; //Add velocity to Particle gravity
	this->position += velocity; //Add our velocity to position
	//p2->velocity += grav;
	//p2->position += p2->velocity;
}
