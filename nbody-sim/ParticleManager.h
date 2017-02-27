#pragma once

#include <GL\glew.h>
#include "Rnd.h"
#include "BarnesHutTree.h"
#include <iostream>
#include <vector>


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

	Quad* quad;
	BarnesHutTree *tree = nullptr;
	ParticleManager();
	virtual ~ParticleManager();
	void cleanUpParticles();
	void init();
	void calculateForces();
	void draw();

	Body* generateBody();

private:
	int particleCount = 1000;
	std::vector<Body*> bodies;	
};

