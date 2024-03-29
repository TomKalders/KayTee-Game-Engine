﻿#include "QbertPCH.h"
#include "CustomObservers.h"
#include "Components.h"
#include "GridPosition.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

GridObserver::GridObserver(bool& levelCompleteRef)
	: m_pLevelCompleted(&levelCompleteRef)
{
	
}

GridObserver::~GridObserver()
{
}

void GridObserver::Notify(GameObject* gameObject, Event event, GameObject* parent)
{
	gameObject;
	parent;

	if (event == Event::levelComplete)
	{
		*m_pLevelCompleted = true;
	}
}

PlayerObserver::PlayerObserver(GameObject* player, bool& playerDied)
	: m_pPlayer(player)
	, m_PlayerDied(&playerDied)
{
}

PlayerObserver::~PlayerObserver()
{
}

void PlayerObserver::Notify(GameObject* gameObject, Event event, GameObject* parent)
{
	parent;
	gameObject;
	
	if (event == Event::playerDamaged)
	{
		auto pHealthText = parent->GetComponents<TextComponent>()[0];
		auto pHealth = m_pPlayer->GetComponent<HealthComponent>();
		if (pHealthText && pHealth)
		{
			int h = pHealth->GetHealth();
			pHealthText->SetText("Lives: " + std::to_string(h));

			SDLSoundSystem* m_SoundSystem = static_cast<SDLSoundSystem*>(ServiceLocator::GetSoundSystem());
			if (m_SoundSystem)
			{
				Sound sound{ "Data/Sounds/swear.wav" };
				SoundID m_Id = m_SoundSystem->AddSound(sound);
				m_SoundSystem->Play(m_Id, 10.f);
			}
		}
	}
	else if (event == Event::playerScored)
	{
		auto pScoreText = parent->GetComponents<TextComponent>()[1];
		auto pScore = m_pPlayer->GetComponent<ScoreComponent>();
		if (pScoreText && pScore)
		{
			int s = pScore->GetScore();
			pScoreText->SetText("Score: " + std::to_string(s));
		}
	}
	else if (event == Event::playerDied)
	{
		auto pHealthText = parent->GetComponents<TextComponent>()[0];
		if (pHealthText)
		{
			//Do something when he dies
			pHealthText->SetText("Lives: Dead");
			*m_PlayerDied = true;
		}
	}
}
