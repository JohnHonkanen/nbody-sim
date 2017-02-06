#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
}


SimulationManager::~SimulationManager()
{
}
/*
	Initializing for Particles
*/
void SimulationManager::init()
{
	this->particle[0] = new Particle(vec2(8000,6000), 500000, vec2(-7.0f, 0));
	this->particle[1] = new Particle(vec2(4000, 4000), 500000, vec2(4.0f, 0));
	this->particle[2] = new Particle(vec2(12000, 9000), 100, vec2(1, -5.0f));
}
/*
	Main Loop for Simulation
*/
void SimulationManager::run(SDL_Window *window) {
	SDL_Event e;
	this->init();
	while (running) {
		SDL_PollEvent(&e);
		running = this->pollEvents(e);
		update();
		draw(window);
	}
}
/*
	Handle Keyboard Events
*/
bool SimulationManager::pollEvents(SDL_Event sdlEvent) {
	if (sdlEvent.type == SDL_QUIT)
		return false;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		case SDLK_e:
			zoom += 0.1f;
			std::cout << "Zooming";
			break;
		case SDLK_q:
			zoom -= 0.1f;
			break;
		default:
			break;
		}
	}	

	return true;
}
/*
	Handle and Calculate Physics for Simulation
*/
void SimulationManager::update() {
	this->particle[0]->accept(this->physicsVisitor, this->particle[1]);
	this->particle[0]->accept(this->physicsVisitor, this->particle[2]);
	this->particle[1]->accept(this->physicsVisitor, this->particle[0]);
	this->particle[1]->accept(this->physicsVisitor, this->particle[2]);
	this->particle[2]->accept(this->physicsVisitor, this->particle[0]);
	this->particle[2]->accept(this->physicsVisitor, this->particle[1]);
	//std::cout << this->particle[0]->position.x << "!!" << this->particle[0]->position.y << std::endl;
}
/*
	Handle Rendering for simulation
*/
void SimulationManager::draw(SDL_Window *window) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, 16000*zoom, 0, 12000*zoom, 0.0f, 1.0f); // Reference system of our simulation
	glColor3f(0.5, 1.0, 1.0);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex3f(this->particle[0]->position.x, this->particle[0]->position.y, 0.0);
	glVertex3f(this->particle[1]->position.x, this->particle[1]->position.y, 0.0);
	glVertex3f(this->particle[2]->position.x, this->particle[2]->position.y, 0.0);
	glEnd();

	SDL_GL_SwapWindow(window); // swap buffers
}
