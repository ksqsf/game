#pragma once

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>

#include "framework.h"
#include "graphics.h"
#include "object.h"

using EventHandler = std::function<bool(SDL_Event)>;

class Scene {
	friend class Framework;
	
public:
	Scene(Graphics& g) noexcept;
	~Scene() noexcept;
	
	void add_object(Object *obj) noexcept;
	void listen(const char *event, EventHandler handler);
	void draw();
	
private:
	Graphics& m_graphics;
	std::vector<Object*> m_objectList;
	std::unordered_map<std::string, std::vector<EventHandler>> m_eventHandlers;
};
