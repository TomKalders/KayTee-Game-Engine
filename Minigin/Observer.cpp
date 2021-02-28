#include "MiniginPCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "Components.h"

dae::Observer::Observer()
{
}

//Player Observer
dae::PlayerObserver::PlayerObserver(GameObject* gameObject, const std::string& playerName, GameObject* goScore)
	: m_GameObject(gameObject)
	, m_ScoreGameObject(goScore)
	, m_Name(playerName)
{
}

void dae::PlayerObserver::Notify(GameObject* gameObject, Event event)
{
	if (gameObject == m_GameObject)
	{
		switch (event)
		{
		case Event::playerDamaged:
		{
			int health = gameObject->GetComponent<HealthComponent>()->GetHealth();
			gameObject->GetComponent<TextComponent>()->SetText(m_Name + " HP: " + std::to_string(health));
		}
		break;

		case Event::playerDied:
			gameObject->GetComponent<TextComponent>()->SetText(m_Name + " HP: Dead");
			break;
		}
	}
	else if (gameObject == m_ScoreGameObject)
	{
		switch (event)
		{
		case Event::playerScored:
		{
			if (m_ScoreGameObject)
			{
				TextComponent* textComp = m_ScoreGameObject->GetComponent<TextComponent>();
				ScoreComponent* scoreComp = m_ScoreGameObject->GetComponent<ScoreComponent>();
				if (textComp && scoreComp)
				{
					textComp->SetText(m_Name + " Score: " + std::to_string(scoreComp->GetScore()));
				}
			}
		}
		break;
		}
	}
}
