#include "exception.h"
#include "scene.h"

Scene::Scene(Graphics& g)
	: m_graphics(g)
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
