#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SubjectComponent.h"

dae::HealthComponent::HealthComponent(int health)
	: m_Health(health)
	, m_MaxHealth(health)
	, m_pSubjectComponent{nullptr}
{
}

dae::HealthComponent::~HealthComponent()
{
}

void dae::HealthComponent::Update(float)
{
}

void dae::HealthComponent::Render() const
{
}

void dae::HealthComponent::Damage(int damage)
{
	m_Health -= damage;

	if (m_Health < 0)
		m_Health = 0;

	if (!m_pSubjectComponent)
		m_pSubjectComponent = m_pParent->GetComponent<SubjectComponent>();

	if (m_pSubjectComponent)
	{
		if (m_Health == 0)
		{
			m_pSubjectComponent->Notify(m_pParent, Event::playerDied);
		}
		else
		{
			m_pSubjectComponent->Notify(m_pParent, Event::playerDamaged);
		}
	}
}

void dae::HealthComponent::Heal(int health)
{
	m_Health += health;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}

void dae::HealthComponent::SetHealth(int health)
{
	m_Health = health;

	if (m_Health < 0)
		m_Health = 0;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}
