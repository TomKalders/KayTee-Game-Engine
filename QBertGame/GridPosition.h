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
	void SetCoordinates(const glm::ivec2& coordinates);
private:
	glm::ivec2 m_Coordinates;
};
