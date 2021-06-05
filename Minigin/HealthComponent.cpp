#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "SubjectComponent.h"

HealthComponent::HealthComponent(int health)
	: m_Health(health)
	, m_MaxHealth(health)
	, m_pSubjectComponent{nullptr}
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(float)
{
}

void HealthComponent::Render() const
{
}

void HealthComponent::Damage(int damage)
{
	m_Health -= damage;

	if (m_Health < 0)
		m_Health = 0;

	if (!m_pSubjectComponent)
		m_pSubjectComponent = m_pParent->GetComponent<SubjectComponent>();

	if (m_pSubjectComponent)
	{
		if (IsDead())
		{
			m_pSubjectComponent->Notify(m_pParent, Event::playerDied);
			m_pSubjectComponent->Notify(m_pParent, Event::playerDamaged);
		}
		else
		{
			m_pSubjectComponent->Notify(m_pParent, Event::playerDamaged);
		}
	}
}

void HealthComponent::Heal(int health)
{
	m_Health += health;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}

int HealthComponent::GetHealth() const
{
	return m_Health;
}

void HealthComponent::SetHealth(int health)
{
	m_Health = health;

	if (m_Health < 0)
		m_Health = 0;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}

bool HealthComponent::IsDead()
{
	return m_Health <= 0;
}
