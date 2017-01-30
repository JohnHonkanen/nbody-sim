#pragma once
#include <SDL.h>
class SimulationManager
{
public:
	SimulationManager();
	virtual ~SimulationManager();
	void run(SDL_Window *window, SDL_Renderer *renderer);
	void update();
	bool pollEvents(SDL_Event e);
	void draw(SDL_Window *window, SDL_Renderer *renderer);
private:
	bool running = true;
};

