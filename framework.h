#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include "graphics.h"
#include "scene.h"

class Scene;

class Framework final {
public:
	Framework(const Graphics& graphics) noexcept;
	~Framework() noexcept;
	
	void run();
	void switch_scene(Scene *scene) noexcept;
	
private:
	void invoke_handlers(const char *event_name, const SDL_Event& e);
	
private:
	Scene        *m_curScene;
	SDL_Renderer *m_renderer;
	SDL_Window   *m_window;
};
