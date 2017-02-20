#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "rt3d.h"
#include "Particle.h"
#include "ParticleManager.h" //Added
#include <iostream>

#define DEG_TO_RADIAN 0.017453293
class SimulationManager
{
public:
	SimulationManager();
	virtual ~SimulationManager();
	void init();
	void run(SDL_Window *window);
	void update();
	bool pollEvents(SDL_Event e);
	void draw(SDL_Window *window);
private:
	bool running = true;
	Physics physicsVisitor;
	float zoom = 1.0f;
	ParticleManager *pManager;
};

