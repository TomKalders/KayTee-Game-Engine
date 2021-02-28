#pragma once
#include "EventEnums.h"

namespace  dae
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:
		Subject();
		virtual ~Subject();
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(GameObject* gameObject, Event event);

	private:
		std::vector<Observer*> m_Observers;
	};

	
}