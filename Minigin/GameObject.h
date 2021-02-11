#pragma once
#include "Transform.h"
#include "SceneObject.h"
//#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		//void Render() const override;

		void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		template <typename T>
		T* GetComponent() const
		{
			for (BaseComponent* component : m_Components)
			{
				if (typeid(component) == typeid(T))
				{
					return dynamic_cast<T*>(component);
				}
			}
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//Transform m_Transform;
		std::vector<BaseComponent*> m_Components;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
