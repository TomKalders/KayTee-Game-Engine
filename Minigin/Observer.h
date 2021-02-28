#pragma once
#include "EventEnums.h"


namespace dae
{	
	class GameObject;

	class Observer
	{
	public:
		Observer();
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Notify(GameObject* gameObject, Event event) = 0;
	};

	class PlayerObserver final : public Observer
	{
	public:
		PlayerObserver(GameObject* gameObject, const std::string& playerName, GameObject* goScore);
		virtual ~PlayerObserver() = default;

		void Notify(GameObject* gameObject, Event event) override;
	private:
		GameObject* m_GameObject;
		GameObject* m_ScoreGameObject;
		std::string m_Name;
	};
}
