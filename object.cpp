#include <cassert>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "logger.h"
#include "exception.h"
#include "object.h"

Object::Object(SDL_Renderer *ren)
	: m_renderer(ren)
	, texture(nullptr)
{
}

Object::~Object()
{
	// Be defensive.
	if (texture) {
		SDL_DestroyTexture(texture);
	}
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

Rectangle::Rectangle(SDL_Renderer *ren, SDL_Color fill, SDL_Color border)
	: Object(ren)
	, m_fill(ren, fill)
	, m_border(ren, border)
{
}

void Rectangle::draw()
{
	m_fill.x = m_border.x = x;
	m_fill.y = m_border.y = y;
	m_fill.width = m_border.width = width;
	m_fill.height = m_border.height = height;
	
	m_fill.draw();
	m_border.draw();
}

Text::Text(SDL_Renderer *ren, const char *text, int size, SDL_Color color)
	: Object(ren)
{
	TTF_Font *sans = TTF_OpenFont(DATA_PATH "/DejaVuSans.ttf", size);
	if (sans == nullptr) {
		log_error("TEXT: Failed to open font, skipping: %s\n", TTF_GetError());
		return;
	}
	SDL_Surface* sur = TTF_RenderText_Solid(sans, text, color);
	texture = SDL_CreateTextureFromSurface(m_renderer, sur);
	SDL_FreeSurface(sur);
}
