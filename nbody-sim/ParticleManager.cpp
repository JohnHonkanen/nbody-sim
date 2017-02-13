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

Particle* ParticleManager::generateParticle()
{
	return new Particle(vec2(rnd(500,3300), rnd(200, 2200)), 1, vec2(30,0));
}

void ParticleManager::init() 
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < this->particleCount - 1; i++)
	{
		addParticle(generateParticle());
	}
	addParticle(new Particle(vec2(1800, 1200), 1e6, vec2(0, 0), false));
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
		
	glBegin(GL_POINTS);

	while (current != nullptr)
	{
		//std::cout << current->particle->position.x << " || " << current->particle->position.y << std::endl;
		glVertex3f(current->particle->position.x, current->particle->position.y, 0.0);
		current = current->next;
	}

	glEnd();
}

void ParticleManager::calculateForces(Physics physics)
{
	ParticleList* current = this->head;

	while (current != nullptr)
	{
		ParticleList* innerCurrent = current->next;
		while (innerCurrent != nullptr)
		{
			current->particle->accept(physics, innerCurrent->particle);
			innerCurrent = innerCurrent->next;
		}
		current->particle->move();
		current = current->next;
	}
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
