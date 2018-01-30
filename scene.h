#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "object.h"

class Scene {
public:
	Scene(SDL_Renderer *ren);
	~Scene();
	
	void add_object(Object *obj);
	void draw();
	
private:
	SDL_Renderer *m_renderer;
	std::vector<Object*> m_objectList;
};
