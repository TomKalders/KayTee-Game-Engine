#include "MiniginPCH.h"
#include "ObserverComponent.h"

ObserverComponent::ObserverComponent(Observer* observer)
	: m_pObserver(observer)
{
}

ObserverComponent::~ObserverComponent()
{
	delete m_pObserver;
	m_pObserver = nullptr;
}

void ObserverComponent::Update(float)
{
}

void ObserverComponent::Render() const
{
}

void ObserverComponent::Notify(GameObject* gameObject, Event event)
{
	m_pObserver->Notify(gameObject, event, m_pParent);
}

