#pragma once
#include <glm\glm.hpp>
#include <iostream>
#include <limits>
using namespace glm;

const double static GRAV_CONST = 6.673E-11;
const double static SOLAR_MASS = 1.98892e30;
const double static EPS = DBL_EPSILON;

class Physics
{
public:
	Physics();
	virtual ~Physics();
	static double calculateForce(dvec2 p1, dvec2 p2, double mass, double mass2);
	static double getLengthOf(dvec2 p);
	static float getAngleOf(dvec2 p);
	static void setAngleOf(dvec2 &p, float angle);
	static void setLengthOf(dvec2 &p, float length);
	static double distanceBetween(dvec2 p1, dvec2 p2);
	static float angleBetween(dvec2 p1, dvec2 p2);
	static double circularOrbit(dvec2 position);
};

