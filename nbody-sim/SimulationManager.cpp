#include "SimulationManager.h"



SimulationManager::SimulationManager()
{
}


SimulationManager::~SimulationManager()
{
}
/*
	Main Loop for Simulation
*/
void SimulationManager::run(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_Event e;
	while (running) {
		SDL_PollEvent(&e);
		running = this->pollEvents(e);
		update();
		draw(window, renderer);
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
		default:
			break;
		}
	}
	return true;
}
/*
	Handle Physics for simulation
*/
void SimulationManager::update() {

}
/*
	Handle Rendering for simulation
*/
void SimulationManager::draw(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //Change Background color to red
	SDL_RenderClear(renderer); //Clears our Window
	SDL_Rect r;
	r.x = 50;
	r.y = 50;
	r.w = 50;
	r.h = 50;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Set rect to blue
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
}
