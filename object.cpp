#include <cassert>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "logger.h"
#include "exception.h"
#include "object.h"

Object::Object(Graphics& g)
	: m_renderer(g.renderer)
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

ImageObject::ImageObject(Graphics& g, const char *pathname)
	: Object(g)
{
	texture = IMG_LoadTexture(m_renderer, pathname);
	if (!texture) {
		throw SDLException(SDL_GetError());
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	x = y = 0;
}

HollowRectangle::HollowRectangle(Graphics& g, SDL_Color color)
	: Object(g)
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

FilledRectangle::FilledRectangle(Graphics& g, SDL_Color color)
	: Object(g)
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

Rectangle::Rectangle(Graphics& g, SDL_Color fill, SDL_Color border)
	: Object(g)
	, m_fill(g, fill)
	, m_border(g, border)
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

Text::Text(Graphics& g, const char *text, int size, SDL_Color color)
	: Object(g)
{
	TTF_Font *sans = TTF_OpenFont(DATA_PATH "/DejaVuSans.ttf", size);
	if (sans == nullptr) {
		log_error("TEXT: Failed to open font, skipping: %s\n", TTF_GetError());
		return;
	}
	SDL_Surface* sur = TTF_RenderText_Solid(sans, text, color);
	texture = SDL_CreateTextureFromSurface(m_renderer, sur);
	SDL_FreeSurface(sur);
	
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}
