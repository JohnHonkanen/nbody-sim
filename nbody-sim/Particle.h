#pragma once
#define _USE_MATH_DEFINES
#include <glm\glm.hpp>
#include <math.h>
#include "Physics.h"
#include <iostream>
class Particle
{
public:
	Particle();
	Particle(glm::vec2 p, float mass);
	Particle(glm::vec2 p, float mass, vec2 initialVelocity);
	Particle(glm::vec2 p, float mass, vec2 initialVelocity, bool canMove);
	virtual ~Particle();
	glm::vec2 position;
	float mass;
	void accept(Physics physics, Particle* p2);
	void move();
private:
	glm::vec2 velocity;
	bool canMove = true;
};

