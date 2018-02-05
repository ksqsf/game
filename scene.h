#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "framework.h"
#include "graphics.h"
#include "object.h"

using EventHandler = std::function<void(SDL_Event)>;

class Scene {
	friend class Framework;
	
public:
	Scene(Graphics& g);
	~Scene();
	
	void add_object(Object *obj);
	void listen(const char *event, EventHandler handler);
	void draw();
	
private:
	Graphics& m_graphics;
	std::vector<Object*> m_objectList;
	std::unordered_map<std::string, std::vector<EventHandler>> m_eventHandlers;
};
