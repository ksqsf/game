#pragma once

struct Graphics final {
	Graphics(const char *title, int width, int height);
	Graphics(const Graphics& rhs) = delete;
	~Graphics() noexcept;
	
	void warp_mouse(int x, int y) noexcept;
	
	SDL_Renderer *renderer;
	SDL_Window *window;
};
