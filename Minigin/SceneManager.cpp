#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(float dt)
{
	if (dt)

	for(auto& scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->Update(dt);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
