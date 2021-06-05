#pragma once
#include "BaseComponent.h"

class GridComponent;
class GridPosition;
class SlickMoveComponent : public BaseComponent
{
public:
	SlickMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval, float respawnTime, int maxNrTiles);
	virtual ~SlickMoveComponent() = default;
	SlickMoveComponent(const SlickMoveComponent& other) = delete;
	SlickMoveComponent(SlickMoveComponent&& other) noexcept = delete;
	SlickMoveComponent& operator=(const SlickMoveComponent& other) = delete;
	SlickMoveComponent& operator=(SlickMoveComponent&& other) = delete;
	
	void Initialize() override;
	void Update(float dt) override;

	void SetPlayer2(GameObject* pPlayer2);
	void SetMoveDirections(const std::vector<glm::ivec2>& moveDirs);
	void HurtPlayer(bool hurt);
	void ReverseTiles(bool reverse);
private:
	GridComponent* m_pGrid;
	GridPosition* m_pPlayerPosition;
	GridPosition* m_pPlayer2Position;
	GridPosition* m_pCurrentPosition;
	GameObject* m_pPlayer;
	std::vector<glm::ivec2> m_MoveDirections;
	const glm::ivec2 m_SlickSleepingSpot;
	float m_Interval;
	float m_CurrentInterval;
	float m_RespawnTime;
	float m_CurrentRespawnTime;
	const int m_NrOfTiles;
	int m_TilesMoved;
	bool m_Disabled;
	bool m_HurtPlayer;
	bool m_ReverseTiles;

	void Move();
	void Disable();
	void Enable();
	bool CheckPlayerHit();
};
