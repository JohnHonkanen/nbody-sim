#pragma once
#define _USE_MATH_DEFINES
#include <glm\glm.hpp>
#include <math.h>
#include "Physics.h"
#include "Rnd.h"
#include "Quad.h"
#include <iostream>
class Particle
{
public:
	Particle();
	Particle(glm::dvec2 p, float mass);
	Particle(glm::dvec2 p, double mass, dvec2 initialVelocity);
	Particle(glm::dvec2 p, double mass, dvec2 initialVelocity, bool canMove);
	Particle(glm::dvec2 p, double mass, dvec2 initialVelocity, bool canMove, int size);
	void accept(Physics physics, Particle* p2);
	void move(double dt);
	void Particle::addForce(Particle* other);
	void Particle::addForce(dvec2 position, double mass);
	void resetForce();
	Particle *add(Particle* p1, Particle* p2);
	double distanceTo(Particle* other);
	bool in(Quad *q);
	virtual ~Particle();
	glm::dvec2 position;
	glm::dvec2 velocity;
	double mass;
	int size = 0;
private:
	const double EPS = DBL_EPSILON;
	const double GRAV_CONST = 6.673E-11;
	glm::dvec2 force;
	bool canMove = true;
};

