#pragma once

#include <vector>
#include <functional>
#include <SDL.h>
#include "object.h"

struct OverlayHandler {
	OverlayHandler(std::function<bool(Object *, Object *)> cb) noexcept;
	OverlayHandler(std::initializer_list<Object*> il, std::function<bool(Object *, Object *)> cb) noexcept;
	void add_object(Object* obj);
	bool operator()(SDL_Event e);
	
private:
	std::vector<Object *> m_objectList;
	std::function<bool(Object *, Object *)> m_callback;
};
