#include "QbertPCH.h"
#include "GridPosition.h"

GridPosition::GridPosition(const glm::ivec2& coordinates)
	: m_Coordinates(coordinates)
	, m_InitialCoordinates(coordinates)
	, m_CanMove(true)
{
}


glm::ivec2 GridPosition::GetCoordinates()
{
	return m_Coordinates;
}

glm::ivec2 GridPosition::GetInitialCoordinates()
{
	return m_InitialCoordinates;
}

bool GridPosition::CanMove()
{
	return m_CanMove;
}

void GridPosition::SetCoordinates(const glm::ivec2& coordinates)
{
	m_Coordinates = coordinates;
}

void GridPosition::CanMove(bool move)
{
	m_CanMove = move;
}
