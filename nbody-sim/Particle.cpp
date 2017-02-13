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

Particle::Particle(glm::vec2 p, float mass, vec2 initialVelocity, bool canMove)
{
	this->velocity = glm::vec2(0, 0);
	this->position = p;
	this->mass = mass; // Mass of Object for particle gravity
	this->velocity = initialVelocity; //Initial Velocity of  Particle
	this->canMove = canMove;
}

Particle::~Particle()
{
}
/*Get the Physics class to do the calculation */
void Particle::accept(Physics physics, Particle* p2)
{
	glm::vec2 grav = physics.calculateGravityFrom(this->position, p2->position, this->mass, p2->mass); // Obtain the gravity vector
	this->velocity += grav; //Add velocity to Particle gravity
	glm::vec2 inverseGrav = grav;
	physics.setAngleOf(inverseGrav, physics.getAngleOf(inverseGrav) + M_PI);
	p2->velocity += inverseGrav;
}
/* Moves the particle with respect to position and velocity*/
void Particle::move()
{
	if(canMove)
		this->position += this->velocity; //Add our velocity to position
}
