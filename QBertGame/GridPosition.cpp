#include "QbertPCH.h"
#include "GridPosition.h"

GridPosition::GridPosition(const glm::ivec2& coordinates)
	: m_Coordinates(coordinates)
	, m_InitialCoordinates(coordinates)
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

void GridPosition::SetCoordinates(const glm::ivec2& coordinates)
{
	m_Coordinates = coordinates;
}
