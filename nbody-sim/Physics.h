#pragma once
#define _USE_MATH_DEFINES
#include <glm\glm.hpp>
#include <iostream>
#include <limits>
using namespace glm;

const double GRAV_CONST = 6.673E-11;
const double SOLAR_MASS = 1.98892e30;
const double EARTH_MASS = 5.972e24;
const double EPS = 3e4;
const double UNIVERSE_RADIUS = 1e18;
const double DEGREE_TO_RADIANS = 0.0174533;

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
	static double circularOrbit(double px, double py);
};

