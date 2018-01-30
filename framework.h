#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "scene.h"

class Framework final {
public:
	Framework(SDL_Window *win, SDL_Renderer *ren);
	~Framework();
	
	void run();
	void switch_scene(Scene *scene);
	
private:
	Scene        *m_curScene;
	SDL_Window   *m_window;
	SDL_Renderer *m_renderer;
};
