#pragma once

#include <GL\glew.h>
#include "Particle.h"
#include "Rnd.h"
#include "BarnesHutTree.h"
#include <iostream>
#include "Rnd.h"


template<typename T>
T signum(T n)
{
	if (n < 0) return -1;
	if (n > 0) return 1;
	return 0;
}

class ParticleManager
{
public:

	struct ParticleList
	{
		Particle* particle;
		ParticleList* next;
		virtual ~ParticleList(){
		}
	};

	Quad* quad;
	BarnesHutTree *tree = nullptr;

	ParticleManager();
	ParticleManager(int particleCount);
	virtual ~ParticleManager();
	void cleanUpParticles();
	void init();
	void addParticle(Particle* p1);
	void calculateForces();
	void draw();

	Particle* generateParticle();
	ParticleList* getHead() { return this->head; }

private:
	ParticleList* head;
	ParticleList* tail;
	int particleCount;
};

