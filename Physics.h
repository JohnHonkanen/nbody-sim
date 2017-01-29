#pragma once
#include "stubParticle.h"

using namespace glm;

class Physics
{
public:
	Physics();
	virtual ~Physics();
	void calculateGravityFrom(stubParticle p2);
	vec2 getVelocity();
	void addStub(stubParticle p);

	stubParticle particle;
private:
	vec2 velocity = vec2(0,0);
	float distanceBetween(vec2 p1, vec2 p2);
	float angleBetween(vec2 p1, vec2 p2);
	//Utility Functions for Physics
	float getLengthOf(vec2 p);
	float getAngleOf(vec2 p);
	void setAngleOf(vec2 &p, float angle);
	void setLengthOf(vec2 &p, float length);
	//End of Utility
};

