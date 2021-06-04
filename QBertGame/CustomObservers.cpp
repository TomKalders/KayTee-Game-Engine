#include "QbertPCH.h"
#include "CustomObservers.h"
#include "Components.h"

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

PlayerObserver::PlayerObserver(GameObject* player)
	: m_pPlayer(player)
{
}

PlayerObserver::~PlayerObserver()
{
}

void PlayerObserver::Notify(GameObject* gameObject, Event event, GameObject* parent)
{
	parent;
	
	if (event == Event::playerDamaged)
	{
		auto pHealthText = gameObject->GetComponent<TextComponent>();
		auto pHealth = m_pPlayer->GetComponent<HealthComponent>();
		if (pHealthText && pHealth)
		{
			int h = pHealth->GetHealth();
			pHealthText->SetText("Health: " + std::to_string(h));
		}
	}
	else if (event == Event::playerScored)
	{
		auto pScoreText = gameObject->GetComponent<TextComponent>();
		auto pScore = m_pPlayer->GetComponent<ScoreComponent>();
		if (pScoreText && pScore)
		{
			int s = pScore->GetScore();
			pScoreText->SetText("Score: " + std::to_string(s));
		}
	}
}
