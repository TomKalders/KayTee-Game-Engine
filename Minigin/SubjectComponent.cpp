#include "MiniginPCH.h"
#include "SubjectComponent.h"

dae::SubjectComponent::SubjectComponent()
	: m_pSubject(new Subject{})
{
}

dae::SubjectComponent::~SubjectComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::SubjectComponent::Update(float)
{
}

void dae::SubjectComponent::Render() const
{
}

void dae::SubjectComponent::AddObserver(ObserverComponent* observer)
{
	//m_pSubject->AddObserver(observer);
	m_Observers.push_back(observer);
}

void dae::SubjectComponent::RemoveObserver(ObserverComponent* observer)
{
	//m_pSubject->RemoveObserver(observer);
	std::vector<ObserverComponent*>::iterator it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (it != m_Observers.end())
	{
		delete* it;
		*it = nullptr;
		m_Observers.erase(it);
	}
}

void dae::SubjectComponent::Notify(GameObject* gameObject, Event event)
{
	for (ObserverComponent* observer : m_Observers)
	{
		observer->Notify(gameObject, event);
	}
	//m_pSubject->Notify(gameObject, event);
}
