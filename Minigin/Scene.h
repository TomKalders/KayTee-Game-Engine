#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Subject;
	
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		//void Add(const std::shared_ptr<SceneObject>& object);
		void Add(GameObject* object);

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
		//std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::vector<GameObject*> m_Objects;
		//std::vector<Subject*> m_Subjects;

		static unsigned int m_IdCounter; 
	};

}
