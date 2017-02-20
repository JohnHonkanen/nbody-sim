#pragma once
#include "Quad.h";
#include "Particle.h"

class BarnesHutTree {
public:
	BarnesHutTree(Quad* q);
	bool isExternal(BarnesHutTree* t);
	void insert(Particle* p);
	void updateForce(Particle* p);
private:
	Particle* particle;
	Quad* quad;
	BarnesHutTree* NW;
	BarnesHutTree* NE;
	BarnesHutTree* SW;
	BarnesHutTree* SE;
};