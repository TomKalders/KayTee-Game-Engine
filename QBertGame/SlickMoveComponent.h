#pragma once
#include "BaseComponent.h"

class GridComponent;
class GridPosition;
class SlickMoveComponent : public BaseComponent
{
public:
	SlickMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval, float respawnTime);
	virtual ~SlickMoveComponent() = default;
	SlickMoveComponent(const SlickMoveComponent& other) = delete;
	SlickMoveComponent(SlickMoveComponent&& other) noexcept = delete;
	SlickMoveComponent& operator=(const SlickMoveComponent& other) = delete;
	SlickMoveComponent& operator=(SlickMoveComponent&& other) = delete;
	
	void Initialize() override;
	void Update(float dt) override;

	void SetPlayer2(GameObject* pPlayer2);
private:
	GridComponent* m_pGrid;
	GridPosition* m_pPlayerPosition;
	GridPosition* m_pPlayer2Position;
	GridPosition* m_pCurrentPosition;
	GameObject* m_pPlayer;
	const glm::ivec2 m_SlickSleepingSpot;
	float m_Interval;
	float m_CurrentInterval;
	float m_RespawnTime;
	float m_CurrentRespawnTime;
	bool m_Disabled;


	void Move();
	void Disable();
	void Enable();
	bool CheckPlayerHit();
};
