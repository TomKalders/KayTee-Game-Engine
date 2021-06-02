#pragma once
#include "BaseComponent.h"
#include <map>

namespace dae
{
class TextureComponent;
}

//struct CmpIVec2 {
//	bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
//		return a.length() < b.length();
//	}
//};

class GridComponent : public dae::BaseComponent
{
public:
	GridComponent(const glm::vec2& position, int width, int height, int cellSize);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;

	void Initialize() override;
	
	glm::ivec2 GetGridLocation(int row, int column);
	glm::ivec2 GetGridCenter(int row, int column);

	void ActivateCell(int row, int column);
private:
	//std::vector<glm::vec2> m_CellPositions;
	std::map<int, TextureComponent*> m_Sprites;
	glm::ivec2 m_Position;
	int m_Width;
	int m_Height;
	int m_CellSize;

	void CreateGrid();
};

