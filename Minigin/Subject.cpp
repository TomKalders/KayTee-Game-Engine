#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	//for (Observer* observer : m_Observers)
	//{
	//	if (observer)
	//	{
	//		delete observer;
	//		observer = nullptr;
	//	}
	//}
}

void Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	std::vector<Observer*>::iterator it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (it != m_Observers.end())
	{
		delete* it;
		*it = nullptr;
		m_Observers.erase(it);
	}
}

void Subject::Notify(GameObject* gameObject, Event event)
{
	for (Observer* observer : m_Observers)
	{
		observer->Notify(gameObject, event);
	}
}
