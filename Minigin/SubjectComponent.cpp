#include "MiniginPCH.h"
#include "SubjectComponent.h"

SubjectComponent::SubjectComponent()
	: m_pSubject(new Subject{})
{
}

SubjectComponent::~SubjectComponent()
{
	delete m_pSubject;
	m_pSubject = nullptr;
}

void SubjectComponent::Update(float)
{
}

void SubjectComponent::Render() const
{
}

void SubjectComponent::AddObserver(ObserverComponent* observer)
{
	//m_pSubject->AddObserver(observer);
	m_Observers.push_back(observer);
}

void SubjectComponent::RemoveObserver(ObserverComponent* observer)
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

void SubjectComponent::Notify(GameObject* gameObject, Event event)
{
	for (ObserverComponent* observer : m_Observers)
	{
		observer->Notify(gameObject, event);
	}
	//m_pSubject->Notify(gameObject, event);
}
