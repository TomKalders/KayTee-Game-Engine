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
	, m_Retrigger(false)
	, m_NrOfTriggers(1)
{
}

void GridComponent::Initialize()
{
	CreateGrid();
}

glm::ivec2 GridComponent::GetGridLocation(int row, int column) const
{
	if (!ValidGridCoordinate(row, column))
	{
		std::cout << "Grid Coordinates Out Of Range!\n";
		return glm::ivec2{ 0, 0 };
	}
	
	int x = (column - row / 2) * m_CellSize + (!(row % 2) * (m_CellSize / 2));
	int y = (row * (3 * m_CellSize / 4));
	glm::ivec2 pos = glm::ivec2{ x, y } + m_Position;
	pos.x -= m_CellSize / 2;
	return pos;
}

glm::ivec2 GridComponent::GetGridCenter(int row, int column) const
{
	glm::ivec2 pos = GetGridLocation(row, column);
	pos.x += m_CellSize / 4;
	pos.y -= m_CellSize / 4;
	return pos;
}

void GridComponent::SetNrOfTriggers(int nrOfTriggers)
{
	m_NrOfTriggers = nrOfTriggers;
}


void GridComponent::ActivateCell(int row, int column)
{
	glm::ivec2 pos = GetGridLocation(row, column);
	int index = row + column * m_Width;

	auto it = m_Sprites.find(index);
	if (it != m_Sprites.end())
	{
		bool triggered = m_Cells.at(index);
		bool result = !(m_Retrigger && triggered);
		m_Cells.at(index) = result;
		++m_TimesSteppedOn.at(index);
		
		if (result && m_TimesSteppedOn.at(index) >= m_NrOfTriggers)
		{
			it->second->SetTexture("Sprites/GridBlockActive.png");
		}
		else
		{
			it->second->SetTexture("Sprites/GridBlock.png");
		}
	}

}

void GridComponent::RetriggerCells(bool retrigger)
{
	m_Retrigger = retrigger;
}

bool GridComponent::RetriggerCells() const
{
	return m_Retrigger;
}


bool GridComponent::AllCellsActive() const
{
	return false;
}

void GridComponent::CreateGrid()
{
	for (int x{}; x < m_Width; x++)
	{
		for (int y{}; y <= x; y++)
		{
			auto pos = GetGridLocation(x, y);
			auto sprite = new TextureComponent{ "Sprites/GridBlock.png", pos };
			int index = x + y * m_Width;
			m_Sprites.insert(std::make_pair(index, sprite));
			m_Cells.insert(std::make_pair(index, false));
			m_TimesSteppedOn.insert(std::make_pair(index, 0));
			m_pParent->AddComponent(sprite);
		}
	}
}

bool GridComponent::ValidGridCoordinate(int row, int column) const
{
	if (row < 0 || row >= m_Height || column > row)
		return false;

	if (column < 0 || column >= m_Width)
		return false;

	return true;
}