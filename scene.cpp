#include "exception.h"
#include "scene.h"

Scene::Scene(SDL_Renderer *ren)
	: m_renderer(ren)
{
}

Scene::~Scene()
{
	for (Object *pObj : m_objectList) {
		delete pObj;
	}
}

void Scene::add_object(Object *obj)
{
	m_objectList.push_back(obj);
}

void Scene::draw()
{
	for (Object *pObj : m_objectList) {
		pObj->draw();
	}
}
