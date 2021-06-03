#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Subject.h"

GameObject::GameObject()
{
	AddComponent(new Transform());
}

GameObject::~GameObject()
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

void GameObject::Update(float dt)
{
	for (BaseComponent* component : m_Components)
	{
		component->Update(dt);
	}
}

void GameObject::Render() const
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
}

void GameObject::AddComponent(BaseComponent* component)
{
	component->SetParent(this);
	component->Initialize();
	m_Components.push_back(component);
}

void GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

std::string GameObject::GetTag() const
{
	return m_Tag;
}

//void GameObject::SetSubject(Subject* subject)
//{
//	if (m_Subject)
//	{
//		delete m_Subject;
//		m_Subject = nullptr;
//	}
//
//	m_Subject = subject;
//}

//Subject* GameObject::GetSubject()
//{
//	return m_Subject;
//}
