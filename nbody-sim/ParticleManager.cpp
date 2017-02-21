#include "ParticleManager.h"

ParticleManager::ParticleManager()
{

}

ParticleManager::ParticleManager(int particleCount)
{
	this->particleCount = particleCount;
	ParticleList* node = new ParticleList();
	node->particle = generateParticle();
	node->next = nullptr;
	this->head = node;
	this->tail = this->head;
	this->quad = new Quad(0, 0, 2 * 1e18);
	tree = new BarnesHutTree(this->quad);
}

ParticleManager::~ParticleManager()
{
	cleanUpParticles();

}

void ParticleManager::cleanUpParticles()
{
	ParticleList* current = this->head;

	while (current != nullptr)
	{
		ParticleList *temp = current;
		current = current->next;
		
		delete temp->particle;
		delete temp;
			
	}
}

Particle* ParticleManager::generateParticle()
{
	double universeRadius = 1e18; //Radius of our Universe;
	double posX = universeRadius*exponent(-1.8)*(.5 - rnd(0,1));
	double posY = universeRadius*exponent(-1.8)*(.5 - rnd(0, 1));
	dvec2 position = dvec2(posX, posY);
	double magV = Physics::circularOrbit(position);
	double absAngle = atan(abs(posY / posX));
	double thetaV = M_PI / 2 - absAngle;

	double vx = -1 * signum(posY)*cos(thetaV)*magV;
	double vy = -1 * signum(posX)*sin(thetaV)*magV;

	//Random Orientation for 2D circular Orbit
	if (rnd(0, 1) <= .5f) {
		vx = -vx;
		vy = -vy;
	}

	double mass = rnd(0, 1) * SOLAR_MASS * 10 + 1e20;
	dvec2 velocity = dvec2(vx,vy);
	
	return new Particle(position, mass, dvec2(0));
}

void ParticleManager::init() 
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < this->particleCount; i++) {
		addParticle(generateParticle());
	}
	//addParticle(new Particle(dvec2(0), 1e6*SOLAR_MASS, dvec2(0)));
}

void ParticleManager::addParticle(Particle* p)
{
	ParticleList* node = new ParticleList();
	node->particle = p;
	node->next = nullptr;
	this->tail->next = node;
	this->tail = this->tail->next;
}

void ParticleManager::draw()
{
	ParticleList* current = this->head;
	glPointSize(1.0f);
	glBegin(GL_POINTS);
	while (current != nullptr)
	{
		glVertex3d(current->particle->position.x, current->particle->position.y, 0.0);
		current = current->next;
		
	}
	glEnd();
	glColor3f(1.0, 0.5, 1.0);

}

void ParticleManager::calculateForces()
{
	tree->clearTree();

	this->quad = new Quad(0, 0, 2 * 1e18);
	tree = new BarnesHutTree(this->quad);
	ParticleList* current = this->head;
	while (current != nullptr) {
		if (current->particle->in(this->quad)) {
			tree->insert(current->particle);
		}
			
		current = current->next;
	}
	current = this->head;
	while (current != nullptr) {

		current->particle->resetForce();
		if (current->particle->in(this->quad)) {
			tree->updateForce(current->particle);
			current->particle->move(1e11);
		}
		current = current->next;
	}
}
