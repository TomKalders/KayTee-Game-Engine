#pragma once
#include "EventEnums.h"

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

	virtual void Notify(GameObject* gameObject, Event event, GameObject* parent = nullptr) = 0;
};

//class PlayerObserver final : public Observer
//{
//public:
//	PlayerObserver(GameObject* gameObject, const std::string& playerName);
//	virtual ~PlayerObserver() = default;
//
//	void Notify(GameObject* gameObject, Event event, GameObject* parent = nullptr) override;
//private:
//	GameObject* m_GameObject;
//	std::string m_Name;
//};