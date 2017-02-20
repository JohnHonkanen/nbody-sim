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
	return new Particle(vec2(rnd(100, 3.6e4), rnd(100, 2.4e4)), rnd(5e10, 5e16), vec2(rnd(-30,30), rnd(-30, 30)));
}

void ParticleManager::init() 
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < this->particleCount - 1; i++)
	{
		addParticle(generateParticle());
	}
	//addParticle(new Particle(vec2(1.8e4, 1.2e4), 5e16, vec2(0, 0), true, 5)); //Error With Physics Code. Need to fix
	//addParticle(new Particle(vec2(1.5e4, 1.3e4), 1e16, vec2(30,10), true, 5));
}

void ParticleManager::addParticle(Particle* p1)
{
	ParticleList* node = new ParticleList();
	node->particle = p1;
	node->next = nullptr;
	this->tail->next = node;
	this->tail = this->tail->next;
}

void ParticleManager::accept(Physics physics)
{
	calculateForces(physics);
}

void ParticleManager::draw()
{
	ParticleList* current = this->head;
		

	while (current != nullptr)
	{
		glPointSize(current->particle->size);
		glBegin(GL_POINTS);
		//std::cout << current->particle->position.x << " || " << current->particle->position.y << std::endl;
		glVertex3f(current->particle->position.x, current->particle->position.y, 0.0);
		current = current->next;
		glEnd();
	}
}

void ParticleManager::calculateForces(Physics physics)
{
	ParticleList* current = this->head;

	while (current != nullptr)
	{
		current->particle->resetForce();
		ParticleList* innerCurrent = this->head;
		while (innerCurrent != nullptr)
		{
			if (innerCurrent != current) {
				current->particle->accept(physics, innerCurrent->particle);
			}
			innerCurrent = innerCurrent->next;
		}
		//current->particle->move();
		current = current->next;
	}

	moveParticles();
}

void ParticleManager::moveParticles()
{
	ParticleList* current = this->head;

	while (current != nullptr)
	{
		current->particle->move();
		current = current->next;
	}
}
