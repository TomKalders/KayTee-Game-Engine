#pragma once
#include "Command.h"

class GridComponent;
class GridPosition;

class Move : public Command
{
public:
	Move(GameObject* pPlayer, GridComponent* pGrid, const glm::ivec2& moveDir);

	void Execute() override;
protected:
	GameObject* m_pPlayer;
	GridComponent* m_pGrid;
	GridPosition* m_pPosition;
	glm::ivec2 m_MoveDir;
};

class MoveRightUp : public Move
{
public:
	MoveRightUp(GameObject* pPlayer, GridComponent* pGrid);
};

class MoveLeftDown : public Move
{
public:
	MoveLeftDown(GameObject* pPlayer, GridComponent* pGrid);
};

class MoveLeftUp : public Move
{
public:
	MoveLeftUp(GameObject* pPlayer, GridComponent* pGrid);
};

class MoveRightDown : public Move
{
public:
	MoveRightDown(GameObject* pPlayer, GridComponent* pGrid);
};
