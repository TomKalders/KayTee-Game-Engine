#pragma once
#include "BaseComponent.h"

class GridComponent;
class GridPosition;

class CoillyMoveComponent : public BaseComponent
{
public:
	CoillyMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval);
	virtual ~CoillyMoveComponent() = default;
	CoillyMoveComponent(const CoillyMoveComponent& other) = delete;
	CoillyMoveComponent(CoillyMoveComponent&& other) noexcept = delete;
	CoillyMoveComponent& operator=(const CoillyMoveComponent& other) = delete;
	CoillyMoveComponent& operator=(CoillyMoveComponent&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;

	void IsPlayerControlled(bool controlled);
private:
	GridComponent* m_pGrid;
	GridPosition* m_pPlayerPosition;
	GridPosition* m_pCurrentPosition;
	GameObject* m_pPlayer;
	float m_Interval;
	float m_CurrentInterval;
	//float m_RespawnTime;
	//float m_CurrentRespawn;
	bool m_FallingDown;
	bool m_PlayerControlled;
	bool m_Disabled;
	bool m_OnPlayer;
	int m_TextureHalfHeight;

	void Move();
	void MoveToPlayer(GridPosition* coillyPos);
	bool CheckPlayerHit(const glm::ivec2& playerCoords, const glm::ivec2& coillyCoords, bool hurtPlayer = true);

	void Disable();
};
