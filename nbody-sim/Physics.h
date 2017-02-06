#pragma once
#include <glm\glm.hpp>
using namespace glm;

class Physics
{
public:
	Physics();
	virtual ~Physics();
	vec2 calculateGravityFrom(vec2 p1, vec2 p2, float mass);
private:
	float distanceBetween(vec2 p1, vec2 p2);
	float angleBetween(vec2 p1, vec2 p2);
	//Utility Functions for Physics
	float getLengthOf(vec2 p);
	float getAngleOf(vec2 p);
	void setAngleOf(vec2 &p, float angle);
	void setLengthOf(vec2 &p, float length);
	//End of Utility
};

