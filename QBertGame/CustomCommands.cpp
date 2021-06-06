#include "QbertPCH.h"
#include "CustomCommands.h"

#include "GridComponent.h"
#include "GridPosition.h"
#include "ServiceLocator.h"

Move::Move(GameObject* pPlayer, GridComponent* pGrid, const glm::ivec2& moveDir, bool IsEnemy)
	: m_pPlayer(pPlayer)
	, m_pGrid(pGrid)
	, m_pPosition(nullptr)
	, m_MoveDir(moveDir)
	, m_IsEnemy(IsEnemy)
{
}

void Move::IsEnemy(bool enemy)
{
	m_IsEnemy = enemy;
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

			if (!m_pPosition->CanMove())
				return;
			
			//If grid coodinate invalid, player should fall off/ take damage.
			if (m_pGrid->ValidGridCoordinate(coords.x, coords.y))
			{
				m_pPosition->SetCoordinates(coords);

				auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
				m_pPlayer->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y) - (m_IsEnemy * 32), 0);
				SDLSoundSystem* m_SoundSystem = static_cast<SDLSoundSystem*>(ServiceLocator::GetSoundSystem());
				if (m_SoundSystem)
				{
					Sound sound{ "Data/Sounds/jump.wav" };
					SoundID m_Id = m_SoundSystem->AddSound(sound);
					m_SoundSystem->Play(m_Id, 1.f);
				}
				
				if (!m_IsEnemy)
				{
					m_pGrid->ActivateCell(coords.x, coords.y);

					if (m_pGrid->IsCellActive(coords.x, coords.y))
					{
						auto score = m_pPlayer->GetComponent<ScoreComponent>();
						if (score)
							score->AddScore(25);
					}
				}
			}
			else
			{
				auto health = m_pPlayer->GetComponent<HealthComponent>();
				if (health)
				{
					health->Damage(1);				
				}

				coords = m_pPosition->GetInitialCoordinates();
				m_pPosition->SetCoordinates(coords);
				auto pos = m_pGrid->GetGridCenter(coords.x, coords.y);
				m_pPlayer->GetComponent<Transform>()->SetPosition(float(pos.x), float(pos.y) - (m_IsEnemy * 32), 0);
			}
		}
	}
}

MoveRightUp::MoveRightUp(GameObject* pPlayer, GridComponent* pGrid, bool isEnemy)
	: Move(pPlayer, pGrid, {-1, 0}, isEnemy)
{
	
}

MoveLeftDown::MoveLeftDown(GameObject* pPlayer, GridComponent* pGrid, bool isEnemy)
	: Move(pPlayer, pGrid, {1, 0}, isEnemy)
{
}

::MoveLeftUp::MoveLeftUp(GameObject* pPlayer, GridComponent* pGrid, bool isEnemy)
	: Move(pPlayer, pGrid, { -1, -1 }, isEnemy)
{
}

MoveRightDown::MoveRightDown(GameObject* pPlayer, GridComponent* pGrid, bool isEnemy)
	: Move(pPlayer, pGrid, { 1, 1 }, isEnemy)
{
}

