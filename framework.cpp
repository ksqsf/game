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
				
			case SDL_MOUSEBUTTONDOWN:
				invoke_handlers("mouse-button-down", e);
				break;
				
			case SDL_MOUSEBUTTONUP:
				invoke_handlers("mouse-button-up", e);
				break;
				
			default:
				break;
			}
		}
		assert(m_curScene != nullptr);
		SDL_RenderClear(m_renderer);
		m_curScene->draw();
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderPresent(m_renderer);
		SDL_Delay(1);
	}
}

void Framework::invoke_handlers(const char *event_name, const SDL_Event& e)
{
	if (m_curScene->m_eventHandlers.count(event_name) == 0) {
		return;
	}
	
	// FIXME: potential race condition!
	for (auto f : m_curScene->m_eventHandlers[event_name]) {
		f(e);
	}
}
