#include <cassert>

#include <SDL2/SDL_image.h>

#include "logger.h"
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

HollowRectangle::HollowRectangle(SDL_Renderer *ren, SDL_Color color)
	: Object(ren)
	, m_color(color)
{
}

void HollowRectangle::draw()
{
	SDL_Rect rect {x, y, width, height};
	if (SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a) != 0) {
		log_error("HRECT: failed to set render draw color, expect to see weird graphics! %s\n",
			SDL_GetError());
	}
	if (SDL_RenderDrawRect(m_renderer, &rect) != 0) {
		log_error("HRECT: failed to draw rect, expect to see weird graphics! %s\n", SDL_GetError());
	}
}

FilledRectangle::FilledRectangle(SDL_Renderer *ren, SDL_Color color)
	: Object(ren)
	, m_color(color)
{
}

void FilledRectangle::draw()
{
	SDL_Rect rect {x, y, width, height};
	if (SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a) != 0) {
		log_error("FRECT: failed to set render draw color, expect to see weird graphics! %s\n",
			SDL_GetError());
	}
	if (SDL_RenderFillRect(m_renderer, &rect) != 0) {
		log_error("FRECT: failed to draw rect, expect to see weird graphics! %s\n", SDL_GetError());
	}
}
