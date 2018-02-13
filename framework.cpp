#include <cassert>
#include <functional>
#include "framework.h"

Framework::Framework(const Graphics& graphics) noexcept
	: m_window(graphics.window)
	, m_renderer(graphics.renderer)
{
}

Framework::~Framework()
{
}

void Framework::switch_scene(std::shared_ptr<Scene> scene) noexcept
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
				
			case SDL_KEYDOWN:
				invoke_handlers("key-down", e);
				break;
				
			default:
				break;
			}
		}
		invoke_alarms();
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
	
	std::vector<EventHandler> &handlers = m_curScene->m_eventHandlers[event_name];
	std::vector<EventHandler> tmp;
	for (auto f : handlers) {
		if (f(e)) {
			tmp.push_back(f);
		}
	}
	handlers = std::move(tmp);
	if (handlers.size() == 0) {
		m_curScene->m_eventHandlers.erase(event_name);
	}
}

void Framework::invoke_alarms()
{
	auto& pq = m_curScene->m_alarmHandlers;
	while (!pq.empty() && pq.top().time <= SDL_GetTicks()) {
		auto cur = pq.top(); pq.pop();
		if (cur.handler()) {
			m_curScene->alarm(cur.interval, std::move(cur.handler));
		}
	}
}
