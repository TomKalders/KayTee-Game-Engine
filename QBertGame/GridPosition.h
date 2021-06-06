#pragma once
#include "BaseComponent.h"

class GridPosition final : public BaseComponent
{
public:
	GridPosition(const glm::ivec2& coordinates);
	virtual ~GridPosition() = default;
	GridPosition(const GridPosition& other) = delete;
	GridPosition(GridPosition&& other) = delete;
	GridPosition& operator=(const GridPosition& other) = delete;
	GridPosition& operator=(GridPosition&& other) = delete;

	glm::ivec2 GetCoordinates();
	glm::ivec2 GetInitialCoordinates();
	bool CanMove();
	void SetCoordinates(const glm::ivec2& coordinates);
	void CanMove(bool move);

private:
	glm::ivec2 m_Coordinates;
	glm::ivec2 m_InitialCoordinates;
	bool m_CanMove;
};
