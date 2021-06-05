#include "QbertPCH.h"
#include "SlickMoveComponent.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "ScoreComponent.h"
#include "glm/gtc/random.hpp"

SlickMoveComponent::SlickMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval, float respawnTime)
	: m_pGrid(pGrid)
	, m_pCurrentPosition(nullptr)
	, m_pPlayerPosition(nullptr)
	, m_pPlayer2Position(nullptr)
	, m_pPlayer(pPlayer)
	, m_Interval(interval)
	, m_CurrentInterval(interval)
	, m_RespawnTime(respawnTime)
	, m_CurrentRespawnTime(respawnTime)
	, m_Disabled(true)
	, m_SlickSleepingSpot({999, 999})
{
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
	if (CheckPlayerHit())
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

void SlickMoveComponent::Move()
{
	if (m_pCurrentPosition->GetCoordinates().x < (m_pGrid->GetHeight()))
	{
		glm::ivec2 coords = m_pCurrentPosition->GetCoordinates();
		if (CheckPlayerHit())
		{
			Disable();
			return;
		}
		int rand = glm::linearRand(0, 1);
		coords.x += 1;
		coords.y += rand;

		m_pCurrentPosition->SetCoordinates(coords);
		auto pos = m_pGrid->GetGridCenter(coords.x, coords.y, true);
		m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);

		m_pGrid->DeactivateCell(coords.x, coords.y);

		if (CheckPlayerHit())
			Disable();
		
		if (!m_pGrid->ValidGridCoordinate(coords.x, coords.y))
		{
			Disable();
		}
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
	}
}

void SlickMoveComponent::Enable()
{
	auto movement = m_pParent->GetComponent<GridPosition>();
	if (movement)
	{
		m_Disabled = false;
		m_CurrentInterval = m_Interval;
		
		int y = glm::linearRand(0, 1);
		movement->SetCoordinates({1, y});
		auto pos = m_pGrid->GetGridCenter(1, y);
		m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);
	}
}

bool SlickMoveComponent::CheckPlayerHit()
{
	if (m_pPlayerPosition->GetCoordinates() == m_pCurrentPosition->GetCoordinates() || 
		(m_pPlayer2Position && (m_pPlayer2Position->GetCoordinates() == m_pCurrentPosition->GetCoordinates())))
	{
		if (m_pPlayer)
		{
			ScoreComponent* score = m_pPlayer->GetComponent<ScoreComponent>();
			if (score)
				score->AddScore(300);
		}
		return true;
	}

	return false;
}

