#pragma once
#include "Quad.h";
#include "Particle.h"

class BarnesHutTree {
public:
	BarnesHutTree(Quad* q);
	virtual ~BarnesHutTree();
	bool isExternal(BarnesHutTree* t);
	void insert(Particle* p);
	void updateForce(Particle* p);
	void draw();
	void clearTree();
private:
	Particle* particle;
	double totalMass = 0;
	dvec2 centerPosition = dvec2(0);
	Quad* quad;
	BarnesHutTree* NW;
	BarnesHutTree* NE;
	BarnesHutTree* SW;
	BarnesHutTree* SE;
};