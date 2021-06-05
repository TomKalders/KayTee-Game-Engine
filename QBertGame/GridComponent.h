#pragma once
#include "BaseComponent.h"
#include <map>


class TextureComponent;
class SubjectComponent;

class GridComponent : public BaseComponent
{
public:
	GridComponent(const glm::vec2& position, int width, int height, int cellSize);
	virtual ~GridComponent() = default;
	GridComponent(const GridComponent& other) = delete;
	GridComponent(GridComponent&& other) = delete;
	GridComponent& operator=(const GridComponent& other) = delete;
	GridComponent& operator=(GridComponent&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	
	glm::ivec2 GetGridLocation(int row, int column) const;
	glm::ivec2 GetGridCenter(int row, int column) const;
	int GetHeight();
	int GetWidth();
	bool ValidGridCoordinate(int row, int column) const;
	int GetCoordinateIndex(int row, int column) const;

	void SetNrOfTriggers(int nrOfTriggers);
	void ActivateCell(int row, int column);
	void DeactivateCell(int row, int column);
	void RetriggerCells(bool retrigger);
	bool RetriggerCells() const;
	bool IsCellActive(int row, int column) const;
	bool GridComplete() const;
private:
	std::map<int, TextureComponent*> m_Sprites;
	std::map<int, bool> m_Cells;
	std::map<int, int> m_TimesSteppedOn;
	
	glm::ivec2 m_Position;
	int m_Width;
	int m_Height;
	int m_CellSize;

	bool m_Retrigger;
	int m_NrOfTriggers;

	void CreateGrid();
	SubjectComponent* m_Subject;
};

