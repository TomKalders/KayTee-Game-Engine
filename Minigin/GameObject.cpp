#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
{
	AddComponent(new Transform());
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* component : m_Components)
	{
		delete component;
		component = nullptr;
	}
}

void dae::GameObject::Update(float dt)
{
	for (BaseComponent* component : m_Components)
	{
		component->Update(dt);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	component->SetParent(this);
	m_Components.push_back(component);
}
