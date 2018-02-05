#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "graphics.h"
#include "object.h"

class Scene {
public:
	Scene(Graphics& g);
	~Scene();
	
	void add_object(Object *obj);
	void draw();
	
private:
	Graphics& m_graphics;
	std::vector<Object*> m_objectList;
};
