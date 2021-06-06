#include "QbertPCH.h"
#include "CoillyMoveComponent.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "TextureComponent.h"
#include "HealthComponent.h"
#include "glm/gtc/random.hpp"

CoillyMoveComponent::CoillyMoveComponent(GridComponent* pGrid, GameObject* pPlayer, float interval)
	: m_pGrid(pGrid)
	, m_pPlayerPosition(nullptr)
	, m_pCurrentPosition(nullptr)
	, m_pPlayer(pPlayer)
	, m_Interval(interval)
	, m_CurrentInterval(interval)
	, m_FallingDown(true)
	, m_PlayerControlled(false)
	, m_TextureHalfHeight(32)
{
}

void CoillyMoveComponent::Initialize()
{
	if (m_pPlayer)
		m_pPlayerPosition = m_pPlayer->GetComponent<GridPosition>();

	m_pCurrentPosition = m_pParent->GetComponent<GridPosition>();
}

void CoillyMoveComponent::Update(float dt)
{
	m_CurrentInterval -= dt;

	if (!m_OnPlayer)
		m_OnPlayer = CheckPlayerHit(m_pPlayerPosition->GetCoordinates(), m_pCurrentPosition->GetCoordinates());
	else
		m_OnPlayer = CheckPlayerHit(m_pPlayerPosition->GetCoordinates(), m_pCurrentPosition->GetCoordinates(), false);
	
	
	if (m_CurrentInterval <= 0)
	{
		Move();
		m_CurrentInterval = m_Interval;
	}
}

void CoillyMoveComponent::IsPlayerControlled(bool controlled)
{
	m_PlayerControlled = controlled;
}

void CoillyMoveComponent::Move()
{
	//auto movement = m_pParent->GetComponent<GridPosition>();
	if (!m_pCurrentPosition)
		return;
	
	if (m_FallingDown)
	{
		m_pCurrentPosition->CanMove(false);
		if (m_pCurrentPosition->GetCoordinates().x < (m_pGrid->GetHeight() - 1))
		{
			glm::ivec2 coords = m_pCurrentPosition->GetCoordinates();
			int rand = glm::linearRand(0, 1);
			coords.x += 1;
			coords.y += rand;

			m_pCurrentPosition->SetCoordinates(coords);
			auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
			m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);
		}
		else
		{
			m_FallingDown = false;
			m_pParent->GetComponent<Transform>()->AddPosition(0, float(-m_TextureHalfHeight), 0);
			auto textureComponent = m_pParent->GetComponent<TextureComponent>();
			if (textureComponent)
				textureComponent->SetTexture("Sprites/Coilly.png");
			m_pCurrentPosition->CanMove(true);
		}
	}
	else
	{
		if (!m_PlayerControlled)
			MoveToPlayer(m_pCurrentPosition);
	}
}

void CoillyMoveComponent::MoveToPlayer(GridPosition* coillyPos)
{
	glm::ivec2 coords = coillyPos->GetCoordinates();
	auto playerCoords = m_pPlayerPosition->GetCoordinates();

	if (CheckPlayerHit(playerCoords, coords))
		return;
	
	//Get all the possible neighbouring tiles
	//and store them in a vector for easier iteration
	glm::ivec2 leftUp = coords + glm::ivec2(-1, -1);
	glm::ivec2 leftDown = coords + glm::ivec2(1, 0);
	glm::ivec2 rightUp = coords + glm::ivec2(-1, 0);
	glm::ivec2 rightDown = coords + glm::ivec2(1, 1);

	std::vector<glm::ivec2> neighbours
	{
		leftUp,
		leftDown,
		rightUp,
		rightDown
	};

	glm::ivec2 playerPos = m_pGrid->GetGridCenter(playerCoords.x, playerCoords.y);
	glm::ivec2 closestNeighbourCoords{ coords };
	float smallestDistance{FLT_MAX};

	for (const glm::ivec2& neighbour : neighbours)
	{
		if (m_pGrid->ValidGridCoordinate(neighbour.x, neighbour.y))
		{
			auto neighbourPos = m_pGrid->GetGridCenter(neighbour.x, neighbour.y);
			glm::vec2 pos = { playerPos - neighbourPos };

			float len1 = glm::length(pos);
			float len2 = smallestDistance;

			if (len1 <= len2)
			{
				smallestDistance = len1;
				closestNeighbourCoords = neighbour;
			}
		}
	}

	coords = closestNeighbourCoords;
	if (m_pGrid->ValidGridCoordinate(coords.x, coords.y))
	{
		coillyPos->SetCoordinates(coords);
		auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
		m_pParent->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y) - m_TextureHalfHeight, 0);
		CheckPlayerHit(playerCoords, coords);
	}
}

bool CoillyMoveComponent::CheckPlayerHit(const glm::ivec2& playerCoords, const glm::ivec2& coillyCoords, bool hurtPlayer)
{
	if (playerCoords == coillyCoords)
	{
		if (hurtPlayer && m_pPlayer)
		{
			HealthComponent* health = m_pPlayer->GetComponent<HealthComponent>();
			if (health)
				health->Damage(1);
		}
		return true;
	}
	
	return false;
}

void CoillyMoveComponent::Disable()
{
	auto textureComponent = m_pParent->GetComponent<TextureComponent>();
	if (textureComponent)
		textureComponent->SetTexture("Sprites/CoillyBall.png");

	auto movement = m_pParent->GetComponent<GridPosition>();
	if (movement)
		movement->SetCoordinates({ 999, 999 });

	m_Disabled;
}
