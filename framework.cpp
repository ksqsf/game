#include <cassert>
#include "framework.h"

Framework::Framework(const Graphics& graphics)
	: m_window(graphics.window)
	, m_renderer(graphics.renderer)
{
}

Framework::~Framework()
{
}

void Framework::switch_scene(Scene *scene)
{
	m_curScene = scene;
}

void Framework::listen(const char *event_name, EventHandler handler)
{
	m_eventHandlers[event_name].push_back(handler);
}

void Framework::run()
{
	SDL_Event e {};
	bool should_quit = false;
	while (!should_quit) {
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
				should_quit = true;
				invoke_handlers("quit", e);
				break;
				
			case SDL_MOUSEMOTION:
				invoke_handlers("mouse-motion", e);
				break;
				
			default:
				break;
			}
		}
		assert(m_curScene != nullptr);
		m_curScene->draw();
		SDL_RenderPresent(m_renderer);
		SDL_Delay(1);
	}
}

void Framework::invoke_handlers(const char *event_name, const SDL_Event& e)
{
	if (m_eventHandlers.count(event_name) == 0)
		return;
	
	for (auto f : m_eventHandlers[event_name]) {
		f(e);
	}
}
