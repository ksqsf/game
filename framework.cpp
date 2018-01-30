#include <cassert>
#include "framework.h"

Framework::Framework(SDL_Window *win, SDL_Renderer *ren)
	: m_window(win)
	, m_renderer(ren)
	, m_curScene(nullptr)
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
