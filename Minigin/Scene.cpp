#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Subject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (SceneObject* object : m_Objects)
	{
		delete object;
		object = nullptr;
	}
	
	for (Subject* subject : m_Subjects)
	{
		delete subject;
		subject = nullptr;
	}
}

void Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Add(Subject* subject)
{
	m_Subjects.push_back(subject);
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

