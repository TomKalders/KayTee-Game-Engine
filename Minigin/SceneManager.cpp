#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

void SceneManager::Render()
{
	m_ActiveScene->Render();
}

void SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](const std::shared_ptr<Scene>& scene)
		{
			return scene->GetName() == name;
		}
	);

	if (it != m_Scenes.end())
	{
		m_ActiveScene = *it;
	}
	else
	{
		if (m_Scenes.size() > 0)
			m_ActiveScene = m_Scenes[0];
	}
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	if (m_ActiveScene.get() == nullptr)
		m_ActiveScene = scene;
	
	return *scene;
}

void SceneManager::RemoveScene(const std::string& name)
{
	auto it = std::remove_if(m_Scenes.begin(), m_Scenes.end(), [name](const std::shared_ptr<Scene>& scene)
		{
			return name == scene->GetName();
		}
	);

	m_Scenes.erase(it);

	if (!m_ActiveScene.get())
	{
		if (m_Scenes.size() > 0)
		{
			m_ActiveScene = m_Scenes[0];
		}
	}
}
