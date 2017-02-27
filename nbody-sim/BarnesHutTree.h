#pragma once
#include "Physics.h"
#include "Quad.h";
#include <iostream>
#include <vector>

#define MAX_DEPTH 100
using namespace std;
const int numberOfPoints = 30;
const float STEP = 2 * M_PI / numberOfPoints;
struct Body {
	Body(double px, double py, double vx, double vy, double mass, double radius, float r, float g, float b) {
		this->px = px;
		this->py = py;
		this->vx = vx;
		this->vy = vy;
		this->mass = mass;
		this->staticBody = false;
		this->r = r;
		this->g = g;
		this->b = b;
		this->radius = radius;
		calculateVertices();
	}
	Body(double px, double py, double vx, double vy, double mass, double radius, float r, float g, float b, bool isStatic) {
		this->px = px;
		this->py = py;
		this->vx = vx;
		this->vy = vy;
		this->mass = mass;
		this->staticBody = isStatic;
		this->r = r;
		this->g = g;
		this->b = b;
		this->radius = radius;
		calculateVertices();
	}
	void calculateVertices() {
		int i = 0;
		for (float angle = 0; angle < 2*M_PI; angle += STEP) {
			double x = this->radius * cos(angle);
			double y = this->radius * sin(angle);
			vertices.push_back(dvec2(x, y));
			i++;
		}
	}
	virtual ~Body() {};
	double px, py;
	double vx, vy;
	double ax = 0; //Acceleration
	double ay = 0;
	double mass;
	double radius;
	bool staticBody;
	float r, g, b;
	std::vector<dvec2> vertices;
	bool in(Quad * q)
	{
		return q->contains(this->px, this->py);
	}
	void update(double dt) {
			vx += dt * ax;
			vy += dt * ay;
			if (!staticBody) {
				px += dt * vx;
				py += dt * vy;
			}
			
	}
	void addForce(double px, double py, double mass)
	{
		double dx = px - this->px;
		double dy = py - this->py;
		double dist = sqrt(dx*dx + dy*dy);
		
		double A= (GRAV_CONST * mass) / ((dist*dist) + (EPS*EPS)); //EPS Dampener
		this->ax += (A*dx / dist);
		this->ay += (A*dy / dist);
	}
	double distanceTo(double cx, double cy, double px, double py) {
		double dx = px - cx;
		double dy = py - cy;
		return sqrt(dx*dx + dy*dy);
	}

	void resetForce() {
		ax = 0.0;
		ay = 0.0;
	}
};
class BarnesHutTree {
public:
	BarnesHutTree(Quad* q, unsigned int depth);
	BarnesHutTree(Quad* q, vector<Body*> bodies, unsigned int depth);
	virtual ~BarnesHutTree();
	void generateChildren();
	void setUpTree(vector<Body*> bodies);
	bool isExternal(BarnesHutTree* t);
	void insert(Body* b);
	void updateForce(Body* b);
	void draw();
	void clearTree();
	void calculateCenterOfMass();
private:
	vector<Body*> bodies;
	double totalMass = 0;
	double cmx, cmy;
	unsigned int depth;
	Quad* quad;
	bool hasChildren = false;
	BarnesHutTree* NW;
	BarnesHutTree* NE;
	BarnesHutTree* SW;
	BarnesHutTree* SE;
};