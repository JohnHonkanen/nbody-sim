#include <SDL.h>
#include "SimulationManager.h"

using namespace std;


bool init() {
	SDL_Init(SDL_INIT_VIDEO); // initialize SDL
	return true;
}


int wmain(int argc, char *argv[])
{
	SDL_GLContext glContext; // OpenGL context handle
	SDL_Window * window; // window handle

	window = SDL_CreateWindow("SDL Test",
		100, 100, 800, 600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	glContext = SDL_GL_CreateContext(window);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!init) {

	}
	else {
		SimulationManager manager = SimulationManager();
		manager.run(window, renderer);
	}
							  // Create 800x600 window

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
