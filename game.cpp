#include <cstdlib>
#include <SDL2/SDL.h>

#include "logger.h"
#include "framework.h"
#include "overlay.h"

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
	
	if (SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND) != 0) {
		log_error("INIT: Failed to set blend mode, expect to see weird graphics! %s\n", 
			SDL_GetError());
	}
	
	Framework framework(win, ren);
	Scene scene(ren);
	
	scene.add_object(new ImageObject(ren, DATA_PATH "/background.bmp"));
	
	FilledRectangle *rect = new FilledRectangle(ren, {0, 0, 255, 255});
	rect->x = rect->y = 0;
	rect->width = rect->height = 100;
	scene.add_object(rect);
	
	HollowRectangle *border = new HollowRectangle(ren, {255, 0, 0, 255});
	border->x = border->y = 0;
	border->width = border->height = 100;
	scene.add_object(border);
	
	FilledRectangle *critical_region = new FilledRectangle(ren, {255, 255, 255, 255});
	critical_region->x = critical_region->y = 400;
	critical_region->width = critical_region->height = 50;
	scene.add_object(critical_region);
	
	auto follow_mouse = [=](SDL_Event e) {
		rect->x = border->x = e.motion.x;
		rect->y = border->y = e.motion.y;
	};
	framework.listen("mouse-motion", follow_mouse);
	
	auto move_back = [=](Object *a, Object *b) {
		b->x = b->y = 0;
		log_info("Moving rect touches the critical region!\n");
	};
	OverlayHandler overlay1(move_back);
	OverlayHandler overlay2(move_back);
	overlay1.add_object(critical_region);
	overlay1.add_object(border);
	overlay2.add_object(critical_region);
	overlay2.add_object(rect);
	framework.listen("mouse-motion", overlay1);
	framework.listen("mouse-motion", overlay2);
	
	framework.switch_scene(&scene);
	framework.run();
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
