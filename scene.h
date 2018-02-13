#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>

#include "framework.h"
#include "graphics.h"
#include "object.h"

using EventHandler = std::function<bool(SDL_Event)>;
using AlarmHandler = std::function<bool()>;

template <typename T>
using min_heap = std::priority_queue< T, std::vector<T>, std::greater<T> >;

struct Alarm {
	uint32_t time;			// the time when the alarm sets off
	uint32_t interval;		// how long between each set-off
	AlarmHandler handler;
	
	bool operator>(const Alarm& rhs) const {
		return time > rhs.time;
	}
};

class Scene {
	friend class Framework;
	
public:
	Scene(Graphics& g) noexcept;
	~Scene();
	
	void add_object(Object *obj) noexcept;
	void listen(const char *event, EventHandler handler);
	void alarm(uint32_t ms, AlarmHandler handler);
	void draw();
	
private:
	Graphics& m_graphics;
	std::vector<Object*> m_objectList;
	std::unordered_map<std::string, std::vector<EventHandler>> m_eventHandlers;
	min_heap<Alarm> m_alarmHandlers;
};
