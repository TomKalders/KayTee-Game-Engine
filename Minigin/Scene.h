#pragma once
#include "SceneManager.h"

class GameObject;
class Subject;

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(GameObject* object);
	void SetActive(bool active);
	bool IsActive();
	std::string GetName();

	void Update(float dt);
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector<GameObject*> m_Objects;

	static unsigned int m_IdCounter;
	bool m_Active;
};