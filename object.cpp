#include <cassert>

#include <SDL2/SDL_image.h>

#include "exception.h"
#include "object.h"

Object::Object(SDL_Renderer *ren)
	: m_renderer(ren)
{
}

Object::~Object()
{
	SDL_DestroyTexture(texture);
}

void Object::draw()
{
	SDL_Rect rect {x, y, width, height};
	
	assert(texture != nullptr);
	if (SDL_RenderCopy(m_renderer, texture, nullptr, &rect) != 0) {
		throw SDLException(SDL_GetError());
	}
}

ImageObject::ImageObject(SDL_Renderer *ren, const char *pathname)
	: Object(ren)
{
	texture = IMG_LoadTexture(m_renderer, pathname);
	if (!texture) {
		throw SDLException(SDL_GetError());
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	x = y = 0;
}
