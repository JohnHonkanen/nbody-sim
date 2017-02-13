#pragma once

#include <GL\glew.h>
#include "Particle.h"
#include "Rnd.h"
#include <iostream>

class ParticleManager
{
public:

	struct ParticleList
	{
		Particle* particle;
		ParticleList* next;
	};

	ParticleManager();
	ParticleManager(int particleCount);
	void init();
	void addParticle(Particle* p1);

	void accept(Physics physics);
	void draw();

	Particle* generateParticle();
	ParticleList* getHead() { return this->head; }

private:
	ParticleList* head;
	ParticleList* tail;
	int particleCount;
	void calculateForces(Physics physics);
	void moveParticles();
};

