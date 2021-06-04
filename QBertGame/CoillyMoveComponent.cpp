#include "QbertPCH.h"
#include "CoillyMoveComponent.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "TextureComponent.h"
#include "glm/gtc/random.hpp"

CoillyMoveComponent::CoillyMoveComponent(GridComponent* pGrid, GridPosition* pPlayerPos, float interval)
	: m_pGrid(pGrid)
	, m_pPlayerPosition(pPlayerPos)
	, m_Interval(interval)
	, m_CurrentInterval(interval)
	, m_FallingDown(true)
	, m_TextureHalfHeight(32)
{
}

void CoillyMoveComponent::Update(float dt)
{
	m_CurrentInterval -= dt;
	if (m_CurrentInterval <= 0)
	{
		Move();
		m_CurrentInterval = m_Interval;
	}
}

void CoillyMoveComponent::Move()
{
	auto movement = m_pParent->GetComponent<GridPosition>();
	if (!movement)
		return;
	
	if (m_FallingDown)
	{
		if (movement->GetCoordinates().x < (m_pGrid->GetHeight() - 1))
		{
			glm::ivec2 coords = movement->GetCoordinates();
			int rand = glm::linearRand(0, 1);
			coords.x += 1;
			coords.y += rand;

			movement->SetCoordinates(coords);
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
		}
	}
	else
	{
		MoveToPlayer(movement);
	}
}

void CoillyMoveComponent::MoveToPlayer(GridPosition* coillyPos)
{
	glm::ivec2 coords = coillyPos->GetCoordinates();
	auto playerCoords = m_pPlayerPosition->GetCoordinates();

	if (playerCoords == coords)
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
	}
}
