#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <logger.h>
#include <framework.h>
#include <overlay.h>

int main()
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		log_fatal("INIT: Failed to initialize SDL: %s\n", SDL_GetError());
		std::exit(EXIT_FAILURE);
	}
	
	// Initialize SDL_ttf.
	if (TTF_Init() < 0) {
		log_fatal("INIT: Failed to initialize SDL_ttf: %s\n", TTF_GetError());
		SDL_Quit();
		std::exit(EXIT_FAILURE);
	}
	
	// Create a window...
	SDL_Window *win = nullptr;
	win = SDL_CreateWindow("Krush", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 
		SDL_WINDOW_SHOWN);
	if (!win) {
		log_fatal("INIT: Failed to create window: %s\n", SDL_GetError());
		SDL_Quit();
		std::exit(EXIT_FAILURE);
	}
	
	// ... and a renderer.
	SDL_Renderer *ren = nullptr;
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!ren) {
		log_fatal("INIT: Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		std::exit(EXIT_FAILURE);
	}
	
	// Set blend mode
	if (SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND) != 0) {
		log_error("INIT: Failed to set blend mode, expect to see weird graphics! %s\n", 
			SDL_GetError());
	}
	
	// Create a framework over the window and the renderer.
	Framework framework(win, ren);
	Scene scene(ren);
	
	// Some dull objects
	scene.add_object(new ImageObject(ren, DATA_PATH "/background.bmp"));
	
	Rectangle *rect = new Rectangle(ren, {0, 0, 255, 255}, {255, 0, 0, 255});
	rect->x = rect->y = 0;
	rect->width = rect->height = 200;
	scene.add_object(rect);
	
	FilledRectangle *critical_region = new FilledRectangle(ren, {255, 255, 255, 255});
	critical_region->x = critical_region->y = 400;
	critical_region->width = critical_region->height = 50;
	scene.add_object(critical_region);
	
	Text *text = new Text(ren, "hello world!");
	text->x = text->y = 200;
	text->width = text->height = 200;
	scene.add_object(text);
	
	// Make the rectangle follow your mouse
	auto follow_mouse = [=](SDL_Event e) {
		rect->x = e.motion.x - rect->width / 2;
		rect->y = e.motion.y - rect->height / 2;
	};
	framework.listen("mouse-motion", follow_mouse);
	
	// When your rectangle touches the critical region, move the rect back.
	auto move_back = [=](Object *a, Object *b) {
		b->x = b->y = 0;
		log_info("Moving rect touches the critical region!\n");
	};
	OverlayHandler overlay2(move_back);
	overlay2.add_object(critical_region);
	overlay2.add_object(rect);
	framework.listen("mouse-motion", overlay2);
	
	// Switch to this scene, and run the event loop.
	framework.switch_scene(&scene);
	framework.run();
	
	// Free the resources.
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
