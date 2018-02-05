#pragma once

#include <SDL2/SDL.h>
#include "graphics.h"

struct Object {
	int x, y, width, height;
	SDL_Texture *texture;
	
	explicit Object(Graphics& g);
	virtual ~Object();
	virtual void draw();
	
protected:
	SDL_Renderer *m_renderer;
};

struct ImageObject : Object {
	ImageObject(Graphics& g, const char *pathname);
};

struct HollowRectangle : Object {
	HollowRectangle(Graphics& g, SDL_Color color);
	void draw() override;
	
private:
	SDL_Color m_color;
};

struct FilledRectangle : Object {
	FilledRectangle(Graphics& g, SDL_Color color);
	void draw() override;
	
private:
	SDL_Color m_color;
};

struct Rectangle : Object {
	Rectangle(Graphics& g, SDL_Color fill, SDL_Color border);
	
	void draw() override;
	
private:
	FilledRectangle m_fill;
	HollowRectangle m_border;
};

struct Text : Object {
	Text(Graphics& g, const char *text = nullptr, int size = 48, SDL_Color color = {0,0,0,255});
};
