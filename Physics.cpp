#include "Physics.h"



Physics::Physics()
{
}


Physics::~Physics()
{
}
/**
Calculate Gravity Pull for Particle p2 on Particle p1
**/
void Physics::calculateGravityFrom(stubParticle p2)
{
	stubParticle p1 = this->particle;
	vec2 gravity = vec2(0, 0);
	float dist = distanceBetween(p1.position,p2.position);
	float angle = angleBetween(p1.position,p2.position);
	float magnitude = p2.mass / (dist*dist); // Calculate Strength of the gravity
	setLengthOf(gravity, magnitude); // Set Strength of the gravity
	setAngleOf(gravity, angle); // Set Direction of the gravity
	this->velocity += gravity; 
	this->particle.position += velocity;
}
vec2 Physics::getVelocity()
{
	return this->velocity;
}

void Physics::addStub(stubParticle p)
{
	this->particle = p;
}
/**
	Get the distance of particle p2 from particle p1
	@param p1 Particle 1 position
	@param p2 Particle 2 position
	@return float Distance from p1 to p2
**/
float Physics::distanceBetween(vec2 p1, vec2 p2)
{
	float dx = p2.x - p1.x; // Difference between p2 x and p1 x
	float dy = p2.y - p1.y; // Difference between p2 y and p1 y
	return sqrt(dx*dx +dy*dy); // Pythagaros of the difference
}
/**
	Get the angle in radians to particle p2 from particle 1
	@param p1 Particle 1 position
	@param p2 Particle 2 position
	@return float Angle from p1 to p2 in radians
**/
float Physics::angleBetween(vec2 p1, vec2 p2)
{
	float dx = p2.x - p1.x; // Difference between p2 x and p1 x
	float dy = p2.y - p1.y; // Difference between p2 y and p1 y
	return atan(dy, dx); // Arc tangeant to get the angle between the two;
}
/*
	returns Length of a vector, in relation to local origin
*/
float Physics::getLengthOf(vec2 p)
{
	return sqrt(p.x*p.x + p.y*p.y);
}
/*
	returns Angle of a vector, in relation to local origin
*/
float Physics::getAngleOf(vec2 p)
{
	return atan(p.x,p.y);
}
/*
	Set the angle of a vector
*/
void Physics::setAngleOf(vec2 & p, float angle)
{
	float length = getLengthOf(p);
	p.x = cos(angle) * length;
	p.y = sin(angle) * length;
}
/*
	Set the magnitude/length of a vector
*/
void Physics::setLengthOf(vec2 & p, float length)
{
	float angle = getAngleOf(p);
	p.x = cos(angle) * length;
	p.y = sin(angle) * length;
}
 