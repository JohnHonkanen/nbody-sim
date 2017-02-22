#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	this->quad = new Quad(0, 0, 2 * 1e18);
	tree = new BarnesHutTree(this->quad);
	this->init();
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::cleanUpParticles()
{
	for (int i = 0; i < this->particleCount; i++) {
		delete this->bodies[i];
	}
}

Body* ParticleManager::generateBody()
{
	double universeRadius = 1e18; //Radius of our Universe;
	double loc = UNIVERSE_RADIUS;

	double posX = UNIVERSE_RADIUS*exponent(-1.8) * (0.5 - rnd(0,1));
	double posY = UNIVERSE_RADIUS*exponent(-1.8) * (0.5 - rnd(0, 1));
	double magV = Physics::circularOrbit(posX, posY);
	double absAngle = atan(abs(posY / posX));
	double thetaV = M_PI / 2 - absAngle;

	double vx = -1 * signum(posY)*cos(thetaV)*magV;
	double vy = signum(posX)*sin(thetaV)*magV;

	//Random Orientation for 2D circular Orbit
	if (rnd(0, 1) <= .5f) {
		vx = -vx;
		vy = -vy;
	}

	double maxValue = 5e10;
	double mass = rnd(5e3,maxValue) * SOLAR_MASS *10+1e20;
	double maxSize = maxValue * SOLAR_MASS * 10 + 1e20;

	float size = (mass/(maxSize)) * 3;
	float r = mass / maxSize+0.1;
	float g = mass / maxSize+0.3;
	float b = mass / maxSize+0.1;
	
	Body *body = new Body(posX, posY, vx, vy, size, r, g, b, mass);
	body->size = size;
	return body;
}

void ParticleManager::init() 
{
	srand((unsigned)time(NULL));
	
	for (int i = 0; i < this->particleCount; i++) {
		this->bodies[i] = generateBody();
	}
	//delete this->bodies[0];
	this->bodies[0] = new Body(0,0 / 2, 0,-1e4 ,1e6*SOLAR_MASS, 10,1,0.4,0.4, true);
	this->bodies[2]->px = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	this->bodies[2]->py = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	this->bodies[3]->px = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	this->bodies[3]->py = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	this->bodies[4]->px = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
	this->bodies[4]->py = rnd(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
}
void ParticleManager::draw()
{
	for (int i = 0; i < this->particleCount; i++) {
		if (this->bodies[i] != nullptr) {
			if (bodies[i]->in(quad)) {
				glPointSize(this->bodies[i]->size);
				glBegin(GL_POINTS);
				glColor3f(this->bodies[i]->r, this->bodies[i]->g, this->bodies[i]->b);
				glVertex3d(this->bodies[i]->px, this->bodies[i]->py, 0.0);
				glEnd();
			}
		}
	}
	//glColor3f(1.0, 0.5, 1.0);
	//tree->draw();
}

void ParticleManager::calculateForces()
{
	tree->clearTree();

	this->quad = new Quad(0, 0, 2 * 1e18);
	tree = new BarnesHutTree(this->quad);

	for (int i = 0; i < this->particleCount; i++) {
		if (this->bodies[i] != nullptr) {
			if (bodies[i]->in(quad)) {
				tree->insert(this->bodies[i]);
			}
		}
	}

	for (int i = 0; i < this->particleCount; i++) {
		if (this->bodies[i] != nullptr) {
			this->bodies[i]->resetForce();
			if (bodies[i]->in(quad)) {
				tree->updateForce(this->bodies[i]);
				this->bodies[i]->update(1e11);
			}
		}
		else {
			delete this->bodies[i];
		}
		
	}
}
