#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class ObserverComponent final : public BaseComponent
{
public:
	ObserverComponent(Observer* observer);
	~ObserverComponent();
	ObserverComponent(const ObserverComponent& other) = delete;
	ObserverComponent(ObserverComponent&& other) noexcept = delete;
	ObserverComponent& operator=(const ObserverComponent& other) = delete;
	ObserverComponent& operator=(ObserverComponent&& other) = delete;

	void Update(float dt) override;
	void Render() const override;
	void Notify(GameObject* gameObject, Event event);

private:
	Observer* m_pObserver = nullptr;
};
