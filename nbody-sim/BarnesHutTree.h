#pragma once
#include "Physics.h"
#include "Quad.h";
#include <iostream>

struct Body {
	Body(double px, double py, double vx, double vy, double mass, float size, float r, float g, float b) {
		this->px = px;
		this->py = py;
		this->vx = vx;
		this->vy = vy;
		this->mass = mass;
		this->staticBody = false;
		this->r = r;
		this->g = g;
		this->b = b;
		this->size = size;
	}
	Body(double px, double py, double vx, double vy, double mass, float size, float r, float g, float b, bool isStatic) {
		this->px = px;
		this->py = py;
		this->vx = vx;
		this->vy = vy;
		this->mass = mass;
		this->staticBody = isStatic;
		this->r = r;
		this->g = g;
		this->b = b;
		this->size = size;
	}
	virtual ~Body() {};
	double px, py;
	double vx, vy;
	//double fx = 0;
	//double fy = 0;
	double ax = 0; //Acceleration
	double ay = 0;
	double mass;
	float size;
	bool staticBody;
	float r, g, b;
	Body* add(Body* b1, Body* b2) {
		double totalMass = b1->mass + b2->mass;
		double cx = (b1->px + b2->px / 2);
		double cy = (b1->py + b2->py / 2);
		int size = b1->size + b2->size;
		return new Body(cx,cy,0,0,totalMass, size, b1->r, b2->g, b1->b);
	}
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
		//double F = GRAV_CONST * (this->mass * mass) / ((dist*dist) + (EPS*EPS));
		double A= (GRAV_CONST * mass) / ((dist*dist) + (EPS*EPS));
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
	BarnesHutTree(Quad* q);
	virtual ~BarnesHutTree();
	bool isExternal(BarnesHutTree* t);
	void insert(Body* b);
	void updateForce(Body* b);
	void draw();
	void clearTree();
private:
	Body* body;
	Body* placeHolder = new Body(0,0,0,0,0,0,0,0,0);
	double totalMass = 0;
	double cmx, cmy;
	Quad* quad;
	BarnesHutTree* NW;
	BarnesHutTree* NE;
	BarnesHutTree* SW;
	BarnesHutTree* SE;
};