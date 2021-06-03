#pragma once
#include "Observer.h"

class GridObserver : public Observer
{
public:
	GridObserver();
	~GridObserver();
	GridObserver(const GridObserver& other) = delete;
	GridObserver(GridObserver&& other) noexcept = delete;
	GridObserver& operator=(const GridObserver& other) = delete;
	GridObserver& operator=(GridObserver&& other) = delete;

	void Notify(GameObject* gameObject, Event event, GameObject* parent) override;
private:
	
};
