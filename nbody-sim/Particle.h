#pragma once
#define _USE_MATH_DEFINES
#include <glm\glm.hpp>
#include <math.h>
#include "Physics.h"
#include "Rnd.h"
#include <iostream>
class Particle
{
public:
	Particle();
	Particle(glm::vec2 p, float mass);
	Particle(glm::vec2 p, double mass, vec2 initialVelocity);
	Particle(glm::vec2 p, double mass, vec2 initialVelocity, bool canMove);
	Particle(glm::vec2 p, double mass, vec2 initialVelocity, bool canMove, int size);
	void accept(Physics physics, Particle* p2);
	void move();
	void resetForce();
	virtual ~Particle();
	glm::vec2 position;
	double mass;
	int size = 0;
private:
	glm::vec2 velocity;
	glm::vec2 force;
	bool canMove = true;
};

