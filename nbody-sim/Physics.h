#pragma once
#include <glm\glm.hpp>
#include <iostream>
#include <limits>
using namespace glm;

class Physics
{
public:
	Physics();
	virtual ~Physics();
	vec2 calculateGravityFrom(vec2 p1, vec2 p2, double mass, double mass2);
	double calculateForce(vec2 p1, vec2 p2, double mass, double mass2);
	float getLengthOf(vec2 p);
	float getAngleOf(vec2 p);
	void setAngleOf(vec2 &p, float angle);
	void setLengthOf(vec2 &p, float length);
	double distanceBetween(vec2 p1, vec2 p2);
	float angleBetween(vec2 p1, vec2 p2);
private:
	const double EPS = DBL_EPSILON;
	const double GRAV_CONST = 6.673E-11;
	//Utility Functions for Physics
	//End of Utility
};

