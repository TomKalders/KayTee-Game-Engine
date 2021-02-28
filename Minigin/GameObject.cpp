#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Subject.h"

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

	//if (m_Subject)
	//{
	//	delete m_Subject;
	//	m_Subject = nullptr;
	//}
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

void dae::GameObject::SetSubject(Subject* subject)
{
	if (m_Subject)
	{
		delete m_Subject;
		m_Subject = nullptr;
	}

	m_Subject = subject;
}

dae::Subject* dae::GameObject::GetSubject()
{
	return m_Subject;
}
