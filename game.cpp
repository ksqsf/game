#include <cstdlib>
#include <SDL2/SDL.h>

#include "logger.h"
#include "framework.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		log_fatal("INIT: Failed to initialize SDL: %s\n", SDL_GetError());
		std::exit(EXIT_FAILURE);
	}
	
	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Krush", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 
		SDL_WINDOW_SHOWN);
	if (!win) {
		log_fatal("INIT: Failed to create window: %s\n", SDL_GetError());
		SDL_Quit();
		std::exit(EXIT_FAILURE);
	}
	
	SDL_Renderer *ren = nullptr;
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!ren) {
		log_fatal("INIT: Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		std::exit(EXIT_FAILURE);
	}
	
	Framework framework(win, ren);
	Scene scene(ren);
	scene.add_object(new ImageObject(ren, "../background.bmp"));
	framework.switch_scene(&scene);
	framework.run();
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
