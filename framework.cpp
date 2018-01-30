#include "framework.h"

Framework::Framework(SDL_Window *win, SDL_Renderer *ren)
	: m_window(win)
	, m_renderer(ren)
{
}

Framework::~Framework()
{
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
		SDL_Delay(1);
	}
}
