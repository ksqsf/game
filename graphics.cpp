#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "exception.h"
#include "logger.h"
#include "graphics.h"

Graphics::Graphics(const char *title, int w, int h)
	: window(nullptr)
	, renderer(nullptr)
{
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw SDLException(SDL_GetError());
	}
	
	// Initialize SDL_ttf.
	if (TTF_Init() < 0) {
		SDL_Quit();
		throw SDLException(TTF_GetError());
	}
	
	// Create a window...
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 
		SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Quit();
		throw SDLException(SDL_GetError());
	}
	
	// ... and a renderer.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw SDLException(SDL_GetError());
	}
	
	// Set blend mode
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0) {
		log_error("INIT: Failed to set blend mode, expect to see weird graphics! %s\n", 
			SDL_GetError());
	}
};

Graphics::~Graphics() noexcept
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::warp_mouse(int x, int y) noexcept
{
	SDL_WarpMouseInWindow(window, x, y);
}
