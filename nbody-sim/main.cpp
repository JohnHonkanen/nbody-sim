#include <glm\glm.hpp>
#include <iostream>
#include <string>
#include <float.h>
#include "Physics.h"

using namespace std;
using namespace glm;
int main()
{
	stubParticle p1;
	p1.position = vec2(50,50);
	p1.mass = 300;

	stubParticle p2;
	p2.position = vec2(-50, -50);
	p2.mass = 300;

	Physics pBody1 = Physics();
	pBody1.addStub(p1);

	Physics pBody2 = Physics();
	pBody2.addStub(p2);

	//Infinite Loop
	while (true) {
		cout << "Particle 1 Position" << endl;
		pBody1.calculateGravityFrom(pBody2.particle);
		cout << pBody1.particle.position.x << " || " << pBody1.particle.position.y << endl;
		cout << "Particle 2 Position" << endl;
		pBody2.calculateGravityFrom(pBody1.particle);
		cout << pBody2.particle.position.x << " || " << pBody2.particle.position.y << endl;
		cin.get();
	}
}
