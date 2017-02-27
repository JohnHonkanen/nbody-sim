#pragma once
#include "Physics.h"
#include "Quad.h";
#include <iostream>
#include <vector>
#define MAX_DEPTH 30

using namespace std;

const int numberOfPoints = 30;
const float STEP = 2 * M_PI / numberOfPoints;
const double maxSize = SOLAR_MASS * 10 + 1e20;
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
	bool checkCollisions(Body* other) {
		float dx = (other->px - this->px);
		float dy = (other->py - this->py);
		//float dz = (p2->position.z - this->position.z); For 3d
		float distance = sqrtf((dx * dx) + (dy * dy));
		//float distance = sqrtf((dx * dx) + (dy * dy) + (dz * dz)); For 3d
		float threshold = (this->radius + other->radius);

		return (distance <= threshold); //If there has been a collision.
	}
	void collisionReaction(Body* other) {
		if ((other->mass) <= this->mass) {
			this->mass = this->mass + other->mass;
			delete other;
		}
		else {
			other->mass = other->mass + this->mass;
			delete this;
		}
	}

	void calculateRadius() {
		this->radius = mass / maxSize * 4e15;
		calculateVertices();
	}
};
class BarnesHutTree {
public:
	BarnesHutTree(Quad* q, unsigned int depth);
	virtual ~BarnesHutTree();
	bool isExternal(BarnesHutTree* t);
	void insert(Body* b);
	void updateForce(Body* b, int &colliding);
	void draw();
	void clearTree();
private:
	vector<Body*> bodies;
	unsigned int depth;
	bool hasBody = false;
	double totalMass = 0;
	double cmx, cmy;
	Quad* quad;
	BarnesHutTree* NW;
	BarnesHutTree* NE;
	BarnesHutTree* SW;
	BarnesHutTree* SE;
};