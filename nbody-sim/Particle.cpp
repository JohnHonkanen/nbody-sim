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
	this->force = glm::vec2(0); //Force
}

Particle::Particle(glm::vec2 p, double mass, vec2 initialVelocity)
{
	this->velocity = glm::vec2(0, 0);
	this->position = p;
	this->mass = mass; // Mass of Object for particle gravity
	this->velocity = initialVelocity; //Initial Velocity of  Particle
	this->force = glm::vec2(0); //Force
	this->size = 1;
}

Particle::Particle(glm::vec2 p, double mass, vec2 initialVelocity, bool canMove)
{
	this->velocity = glm::vec2(0, 0);
	this->position = p;
	this->mass = mass; // Mass of Object for particle gravity
	this->velocity = initialVelocity; //Initial Velocity of  Particle
	this->canMove = canMove;
	this->size = 1;
}

Particle::Particle(glm::vec2 p, double mass, vec2 initialVelocity, bool canMove, int size)
{
	this->velocity = glm::vec2(0, 0);
	this->position = p;
	this->mass = mass; // Mass of Object for particle gravity
	this->velocity = initialVelocity; //Initial Velocity of  Particle
	this->canMove = canMove;
	this->size = size;
}

Particle::~Particle()
{
}
/*Get the Physics class to do the calculation */
void Particle::accept(Physics physics, Particle* p2)
{
	/*
	glm::vec2 grav = physics.calculateGravityFrom(this->position, p2->position, this->mass, p2->mass); // Obtain the gravity vector
	this->force += grav; //Add velocity to Particle gravity
	glm::vec2 inverseGrav = grav;
	double angle = physics.angleBetween(p2->position, this->position);
	physics.setAngleOf(inverseGrav, angle);
	p2->force += inverseGrav;
	*/
	double dx = p2->position.x - this->position.x;
	double dy = p2->position.y - this->position.y;
	double dist = sqrt(dx*dx + dy*dy);
	double F = physics.calculateForce(this->position, p2->position, this->mass, p2->mass);
	this->force = glm::vec2(this->force.x + (F * dx/dist), this->force.y + (F * dy / dist));
}

void Particle::addForce(Particle* other) {
	double dx = other->position.x - this->position.x;
	double dy = other->position.y - this->position.y;
	double dist = sqrt(dx*dx + dy*dy);
	double F = GRAV_CONST * (this->mass * other->mass) / ((dist*dist) + (EPS*EPS));
	this->force = glm::vec2(this->force.x + (F * dx / dist), this->force.y + (F * dy / dist));
}
/* Moves the particle with respect to position and velocity*/
void Particle::move()
{
	if (canMove) {
		this->velocity += glm::vec2(this->force.x / this->mass, this->force.y / this->mass);
		this->position += this->velocity; //Add our velocity to position

	}
}

void Particle::resetForce()
{
	this->force = glm::vec2(0);
}

Particle * Particle::add(Particle * p1, Particle * p2)
{
	double addedmass = p1->mass + p2->mass;
	vec2 addedPosition = (p1->position + p2->position);
	vec2 middlePosition = glm::vec2(addedPosition.x / 2, addedPosition.y / 2);

	return new Particle(middlePosition, addedmass);


}

double Particle::distanceTo(Particle * other)
{
	double dx = other->position.x - this->position.x; // Difference between p2 x and p1 x
	double dy = other->position.y - this->position.y; // Difference between p2 y and p1 y
	return sqrt(dx*dx + dy*dy); // Pythagaros of the difference
}

bool Particle::in(Quad * q)
{
	return q->contains(this->position.x, this->position.y);
}
