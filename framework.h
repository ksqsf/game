#pragma once

#include <SDL.h>
#include <memory>

#include "graphics.h"
#include "scene.h"

class Scene;

class Framework final {
public:
	Framework(const Graphics& graphics) noexcept;
	Framework(const Framework& rhs) = delete;
	~Framework();
	
	void run();
	void switch_scene(std::shared_ptr<Scene> scene) noexcept;
	
private:
	void invoke_handlers(const char *event_name, const SDL_Event& e);
	void invoke_alarms();
	
private:
	std::shared_ptr<Scene> m_curScene;
	SDL_Renderer *m_renderer;
	SDL_Window   *m_window;
};
