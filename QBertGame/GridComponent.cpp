#include "QbertPCH.h"
#include "GridComponent.h"
#include "TextureComponent.h"

#include "GameObject.h"

GridComponent::GridComponent(const glm::vec2& position, int width, int height, int cellSize)
	: BaseComponent()
	, m_Position(position)
	, m_Width(width)
	, m_Height(height)
	, m_CellSize(cellSize)
{
}

void GridComponent::Initialize()
{
	CreateGrid();
}

glm::ivec2 GridComponent::GetGridLocation(int row, int column)
{
	if (row < 0 || row >= m_Width || column < 0 || column >= m_Height)
	{
		std::cout << "Grid Coordinates Out Of Range!\n";
		//return glm::ivec2{ 0, 0 };
	}
	
	int x = (column - row / 2) * m_CellSize + (!(row % 2) * (m_CellSize / 2));
	int y = (row * (3 * m_CellSize / 4));
	glm::ivec2 pos = glm::ivec2{ x, y } + m_Position;
	pos.x -= m_CellSize / 2;
	return pos;
}

glm::ivec2 GridComponent::GetGridCenter(int row, int column)
{
	glm::ivec2 pos = GetGridLocation(row, column);
	pos.x += m_CellSize / 4;
	pos.y -= m_CellSize / 4;
	return pos;
}

void GridComponent::ActivateCell(int row, int column)
{
	glm::ivec2 pos = GetGridLocation(row, column);
	int index = row + column * m_Width;

	auto it = m_Sprites.find(index);
	if (it != m_Sprites.end())
	{
		it->second->SetTexture("Sprites/GridBlockActive.png");
	}
}

void GridComponent::CreateGrid()
{
	for (int y{}; y < m_Width; y++)
	{
		for (int x{}; x <= y; x++)
		{
			auto pos = GetGridLocation(y, x);
			auto sprite = new dae::TextureComponent{ "Sprites/GridBlock.png", pos };
			int index = y + x * m_Width;
			m_Sprites.insert(std::make_pair(index, sprite));
			m_pParent->AddComponent(sprite);
		}
	}
}
