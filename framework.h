#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include "graphics.h"
#include "scene.h"

using EventHandler = std::function<void(SDL_Event)>;

class Framework final {
public:
	Framework(const Graphics& graphics);
	~Framework();
	
	void listen(const char *event_name, EventHandler handler);
	void run();
	void switch_scene(Scene *scene);
	
private:
	void invoke_handlers(const char *event_name, const SDL_Event& e);
	
private:
	Scene        *m_curScene;
	SDL_Renderer *m_renderer;
	SDL_Window   *m_window;
	std::unordered_map<std::string, std::vector<EventHandler>> m_eventHandlers;
};
