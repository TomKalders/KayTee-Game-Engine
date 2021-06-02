#include "QbertPCH.h"
#include "GridPosition.h"

GridPosition::GridPosition(const glm::ivec2& coordinates)
	: m_Coordinates(coordinates)
{
}

glm::ivec2 GridPosition::GetCoordinates()
{
	return m_Coordinates;
}

void GridPosition::SetCoordinates(const glm::ivec2& coordinates)
{
	m_Coordinates = coordinates;
}
