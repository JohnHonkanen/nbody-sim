#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
}


SimulationManager::~SimulationManager()
{
	delete pManager;

}
/*
	Initializing for Particles
*/
void SimulationManager::init()
{
	pManager = new ParticleManager(350);
	pManager->init();
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

	pManager->accept(physicsVisitor);

}
/*
	Handle Rendering for simulation
*/
void SimulationManager::draw(SDL_Window *window) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, 3.6e4*zoom, 0, 2.4e4*zoom, 0.0f, 1.0f); // Reference system of our simulation
	glColor3f(0.5, 1.0, 1.0);

	pManager->draw();

	SDL_GL_SwapWindow(window); // swap buffers
}
