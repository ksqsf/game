#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Framework final {
public:
	Framework(SDL_Window *win, SDL_Renderer *ren);
	~Framework();
	
	void run();
	
private:
	SDL_Window   *m_window;
	SDL_Renderer *m_renderer;
};
