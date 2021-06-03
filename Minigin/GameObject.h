#pragma once
#include "Transform.h"
#include "SceneObject.h"

class BaseComponent;


	class Texture2D;
	class Subject;
	
	class GameObject final
	{
	public:
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Public member functions
		void Update(float dt);
		void Render() const;
		
		void AddComponent(BaseComponent* component);
		void SetTag(const std::string& tag);
		std::string GetTag() const;

		//Templated Functions
		template <typename T>
		T* GetComponent() const;

		template <typename T>
		std::vector<T*> GetComponents() const;

	private:
		std::vector<BaseComponent*> m_Components;
		std::string m_Tag;
	};

	//Templated Functions
	template <typename T>
	inline T* GameObject::GetComponent() const
	{
		for (BaseComponent* component : m_Components)
		{
			T* castedPtr = dynamic_cast<T*>(component);
			if (castedPtr != nullptr)
			{
				return castedPtr;
			}
		}
		return nullptr;
	}

	template <typename T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		std::vector<T*> components;
		for (BaseComponent* component : m_Components)
		{
			T* castedPtr = dynamic_cast<T*>(component);
			if (castedPtr != nullptr)
			{
				components.push_back(castedPtr);
			}
		}
		return components;
	}

