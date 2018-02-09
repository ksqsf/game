#include "exception.h"
#include "scene.h"

Scene::Scene(Graphics& g) noexcept
	: m_graphics(g)
{
}

Scene::~Scene() noexcept
{
	for (Object *pObj : m_objectList) {
		delete pObj;
	}
}

void Scene::add_object(Object *obj) noexcept
{
	m_objectList.push_back(obj);
}

void Scene::listen(const char *event, EventHandler handler)
{
	m_eventHandlers[event].push_back(handler);
}

void Scene::draw()
{
	for (Object *pObj : m_objectList) {
		pObj->draw();
	}
}
