#include "MiniginPCH.h"
#include "ObserverComponent.h"

dae::ObserverComponent::ObserverComponent(Observer* observer)
	: m_pObserver(observer)
{
}

dae::ObserverComponent::~ObserverComponent()
{
	delete m_pObserver;
	m_pObserver = nullptr;
}

void dae::ObserverComponent::Update(float)
{
}

void dae::ObserverComponent::Render() const
{
}

void dae::ObserverComponent::Notify(GameObject* gameObject, Event event)
{
	m_pObserver->Notify(gameObject, event, m_pParent);
}

