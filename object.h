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

struct HollowRectangle : virtual Object {
	HollowRectangle(SDL_Renderer *ren, SDL_Color color);
	void draw() override;
	
private:
	SDL_Color m_color;
};

struct FilledRectangle : Object {
	FilledRectangle(SDL_Renderer *ren, SDL_Color color);
	void draw() override;
	
private:
	SDL_Color m_color;
};

struct Rectangle : Object {
	Rectangle(SDL_Renderer *ren, SDL_Color fill, SDL_Color border);
	
	void draw() override;
	
private:
	FilledRectangle m_fill;
	HollowRectangle m_border;
};

struct Text : Object {
	Text(SDL_Renderer *ren, const char *text = nullptr, int size = 48, SDL_Color color = {255,255,255,255});
};
