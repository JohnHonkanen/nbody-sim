#pragma once
#include <glm\glm.hpp>
#include "Physics.h"
#include <iostream>
class Particle
{
public:
	Particle();
	Particle(glm::vec2 p, float mass);
	Particle(glm::vec2 p, float mass, vec2 initialVelocity);
	virtual ~Particle();
	glm::vec2 position;
	float mass;
	void accept(Physics physics, Particle* p2);
private:
	glm::vec2 velocity;
};

