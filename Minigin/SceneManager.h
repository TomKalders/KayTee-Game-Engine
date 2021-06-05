#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	void RemoveScene(const std::string& name);
	
	void Update(float dt);
	void Render();
	void SetActiveScene(const std::string& name);
	std::shared_ptr<Scene> GetActiveScene();
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_ActiveScene;
};