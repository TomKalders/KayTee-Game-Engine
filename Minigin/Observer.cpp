#include "MiniginPCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "Components.h"

Observer::Observer()
{
}

//Player Observer
//PlayerObserver::PlayerObserver(GameObject* gameObject, const std::string& playerName)
//	: m_GameObject(gameObject)
//	, m_Name(playerName)
//{
//}
//
//void PlayerObserver::Notify(GameObject* gameObject, Event event, GameObject* parent)
//{
//	if (parent && gameObject == m_GameObject)
//	{
//		switch (event)
//		{
//		case Event::playerDamaged:
//		{
//			int health = gameObject->GetComponent<HealthComponent>()->GetHealth();
//			parent->GetComponents<TextComponent>().at(1)->SetText(m_Name + " HP: " + std::to_string(health));
//		}
//		break;
//
//		case Event::playerDied:
//			parent->GetComponents<TextComponent>().at(1)->SetText(m_Name + " HP: Dead");
//			break;
//
//		case Event::playerScored:
//		{
//
//			TextComponent* textComp = parent->GetComponent<TextComponent>();
//			ScoreComponent* scoreComp = m_GameObject->GetComponent<ScoreComponent>();
//			if (textComp && scoreComp)
//			{
//				textComp->SetText(m_Name + " Score: " + std::to_string(scoreComp->GetScore()));
//			}
//		}
//		break;
//		}
//	}
//}
