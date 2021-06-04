#include "QbertPCH.h"
#include "QBertApplication.h"
#include "CustomObservers.h"

GridObserver::GridObserver(bool& levelCompleteRef)
	: m_pLevelCompleted(&levelCompleteRef)
{
	
}

GridObserver::~GridObserver()
{
}

void GridObserver::Notify(GameObject* gameObject, Event event, GameObject* parent)
{
	gameObject;
	parent;

	if (event == Event::levelComplete)
	{
		std::cout << "Level Completed\n";
		*m_pLevelCompleted = true;
	}
}
