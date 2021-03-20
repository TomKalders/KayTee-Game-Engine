#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (GameObject* object : m_Objects)
	{
		delete object;
		object = nullptr;
	}
}

void Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float dt)
{
	for(auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

