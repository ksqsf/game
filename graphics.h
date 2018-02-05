#pragma once

struct Graphics final {
	Graphics(const char *title, int width, int height);
	Graphics(const Graphics& rhs) = delete;
	~Graphics();
	
	SDL_Renderer *renderer;
	SDL_Window *window;
};
