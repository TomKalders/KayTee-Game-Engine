#include "QbertPCH.h"
#include "CustomCommands.h"

#include "GridComponent.h"
#include "GridPosition.h"

Move::Move(GameObject* pPlayer, GridComponent* pGrid, const glm::ivec2& moveDir)
	: m_pPlayer(pPlayer)
	, m_pGrid(pGrid)
	, m_pPosition(nullptr)
	, m_MoveDir(moveDir)
{
}

void Move::Execute()
{
	if (m_pPlayer && m_pGrid)
	{
		if (!m_pPosition)
			m_pPosition = m_pPlayer->GetComponent<GridPosition>();

		if (m_pPosition)
		{
			auto coords = m_pPosition->GetCoordinates();
			coords += m_MoveDir;
			
			//TODO: If grid coodinate invalid, player should fall off.
			if (m_pGrid->ValidGridCoordinate(coords.x, coords.y))
			{
				m_pPosition->SetCoordinates(coords);

				auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
				m_pPlayer->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y), 0);
				m_pGrid->ActivateCell(coords.x, coords.y);
				std::cout << coords.x << ", " << coords.y << "\n";
			}
			else
			{
				auto subject = m_pPlayer->GetComponent<SubjectComponent>();
				if (subject)
					subject->Notify(m_pPlayer, Event::playerDamaged);
			}
		}
	}
}

MoveRightUp::MoveRightUp(GameObject* pPlayer, GridComponent* pGrid)
	: Move(pPlayer, pGrid, {-1, 0})
{
	
}

MoveLeftDown::MoveLeftDown(GameObject* pPlayer, GridComponent* pGrid)
	: Move(pPlayer, pGrid, {1, 0})
{
}

::MoveLeftUp::MoveLeftUp(GameObject* pPlayer, GridComponent* pGrid)
	: Move(pPlayer, pGrid, { -1, -1 })
{
}

MoveRightDown::MoveRightDown(GameObject* pPlayer, GridComponent* pGrid)
	: Move(pPlayer, pGrid, { 1, 1 })
{
}

