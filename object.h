#pragma once

#include <SDL2/SDL.h>

struct Object {
	int x, y, width, height;
	SDL_Texture *texture;
	
	explicit Object(SDL_Renderer *ren);
	virtual ~Object();
	virtual void draw();
	
protected:
	SDL_Renderer *m_renderer;
};

struct ImageObject : Object {
	ImageObject(SDL_Renderer *ren, const char *pathname);
};
