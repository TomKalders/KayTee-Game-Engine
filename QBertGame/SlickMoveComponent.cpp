#include "QbertPCH.h"
#include "SlickMoveComponent.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "glm/gtc/random.hpp"

SlickMoveComponent::SlickMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval, float respawnTime, int maxNrTiles)
	: m_pGrid(pGrid)
	, m_pCurrentPosition(nullptr)
	, m_pPlayerPosition(nullptr)
	, m_pPlayer2Position(nullptr)
	, m_pPlayer(pPlayer)
	, m_Interval(interval)
	, m_CurrentInterval(interval)
	, m_RespawnTime(respawnTime)
	, m_CurrentRespawnTime(respawnTime)
	, m_NrOfTiles(maxNrTiles)
	, m_TilesMoved(0)
	, m_Disabled(true)
	, m_HurtPlayer(false)
	, m_ReverseTiles(true)
	, m_OnPlayer(false)
	, m_SlickSleepingSpot({999, 999})
{
	m_MoveDirections = { {1, 0}, {1, 1} };
}

void SlickMoveComponent::Initialize()
{
	if (m_pPlayer)
		m_pPlayerPosition = m_pPlayer->GetComponent<GridPosition>();

	auto movement = m_pParent->GetComponent<GridPosition>();
	if (movement)
		m_pCurrentPosition = movement;
	
	Disable();
}

void SlickMoveComponent::Update(float dt)
{
	if (!m_OnPlayer && CheckPlayerHit() && !m_HurtPlayer)
	{
		Disable();
	}
	
	if (m_Disabled)
	{
		m_CurrentRespawnTime -= dt;
		if (m_CurrentRespawnTime <= 0)
		{
			Enable();
			m_CurrentRespawnTime = m_RespawnTime;
		}
	}
	else
	{
		m_CurrentInterval -= dt;
		if (m_CurrentInterval <= 0)
		{
			Move();
			m_CurrentInterval = m_Interval;
		}
	}
}

void SlickMoveComponent::SetPlayer2(GameObject* pPlayer2)
{
	auto movement = pPlayer2->GetComponent<GridPosition>();
	if (movement)
		m_pPlayer2Position = movement;
}

void SlickMoveComponent::SetMoveDirections(const std::vector<glm::ivec2>& moveDirs)
{
	m_MoveDirections = moveDirs;
}

void SlickMoveComponent::HurtPlayer(bool hurt)
{
	m_HurtPlayer = hurt;
}

void SlickMoveComponent::ReverseTiles(bool reverse)
{
	m_ReverseTiles = reverse;
}

void SlickMoveComponent::Move()
{
	glm::ivec2 coords = m_pCurrentPosition->GetCoordinates();
	if (CheckPlayerHit() && !m_HurtPlayer)
	{
		Disable();
		return;
	}
	int rand = glm::linearRand(0, int(m_MoveDirections.size() - 1));
	coords += m_MoveDirections[rand];
	
	m_pCurrentPosition->SetCoordinates(coords);
	auto pos = m_pGrid->GetGridCenter(coords.x, coords.y, true);
	m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);

	if (m_ReverseTiles)
		m_pGrid->DeactivateCell(coords.x, coords.y);

	if (CheckPlayerHit() && !m_HurtPlayer)
		Disable();

	++m_TilesMoved;
	if (m_TilesMoved >= m_NrOfTiles)
	{
		Disable();
	}

	if (!m_pGrid->ValidGridCoordinate(coords.x, coords.y))
	{
		Disable();
	}
}

void SlickMoveComponent::Disable()
{
	auto movement = m_pParent->GetComponent<GridPosition>();
	if (movement)
	{
		m_Disabled = true;
		movement->SetCoordinates(m_SlickSleepingSpot);
		auto pos = m_pGrid->GetGridCenter(m_SlickSleepingSpot.x, m_SlickSleepingSpot.y, true);
		m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);
		m_TilesMoved = 0;
	}
}

void SlickMoveComponent::Enable()
{
	auto movement = m_pParent->GetComponent<GridPosition>();
	if (movement)
	{
		m_Disabled = false;
		m_CurrentInterval = m_Interval;

		movement->SetCoordinates(movement->GetInitialCoordinates());
		auto coords = movement->GetCoordinates();
		auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
		m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);
	}
}

bool SlickMoveComponent::CheckPlayerHit()
{
	if (m_Disabled)
		return false;
	
	if (m_pPlayerPosition->GetCoordinates() == m_pCurrentPosition->GetCoordinates() || 
		(m_pPlayer2Position && (m_pPlayer2Position->GetCoordinates() == m_pCurrentPosition->GetCoordinates())))
	{
		if (m_pPlayer)
		{
			if (!m_HurtPlayer)
			{
				ScoreComponent* score = m_pPlayer->GetComponent<ScoreComponent>();
				if (score)
					score->AddScore(300);
			}
			else
			{
				HealthComponent* health = m_pPlayer->GetComponent<HealthComponent>();
				if (health)
					health->Damage(1);
				m_OnPlayer = true;
			}
		}
		return true;
	}

	m_OnPlayer = false;
	return false;
}

