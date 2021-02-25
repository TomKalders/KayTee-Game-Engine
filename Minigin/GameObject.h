#pragma once
#include "Transform.h"
#include "SceneObject.h"

class BaseComponent;

namespace dae
{
	class Texture2D;
	
	class GameObject final : public SceneObject
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Public member functions
		void Update(float dt) override;
		void Render() const override;
		
		void AddComponent(BaseComponent* component);

		//Templated Functions
		template <typename T>
		T* GetComponent() const;


	private:
		std::vector<BaseComponent*> m_Components;
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
}

