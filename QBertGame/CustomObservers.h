#pragma once
#include "Observer.h"

class GridObserver : public Observer
{
public:
	GridObserver(bool& levelCompleteRef);
	virtual ~GridObserver();
	GridObserver(const GridObserver& other) = delete;
	GridObserver(GridObserver&& other) noexcept = delete;
	GridObserver& operator=(const GridObserver& other) = delete;
	GridObserver& operator=(GridObserver&& other) = delete;

	void Notify(GameObject* gameObject, Event event, GameObject* parent) override;
private:
	bool* m_pLevelCompleted;
};

class PlayerObserver : public Observer
{
public:
	PlayerObserver(GameObject* player);
	virtual ~PlayerObserver();
	PlayerObserver(const PlayerObserver& other) = delete;
	PlayerObserver(PlayerObserver&& other) noexcept = delete;
	PlayerObserver& operator=(const PlayerObserver& other) = delete;
	PlayerObserver& operator=(PlayerObserver&& other) = delete;

	void Notify(GameObject* gameObject, Event event, GameObject* parent) override;
private:
	GameObject* m_pPlayer;
};