#include "MiniginPCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "Components.h"

dae::Observer::Observer()
{
}

//Player Observer
dae::PlayerObserver::PlayerObserver(GameObject* gameObject, const std::string& playerName)
	: m_GameObject(gameObject)
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
}
