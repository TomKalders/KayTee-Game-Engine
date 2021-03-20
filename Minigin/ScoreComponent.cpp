#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "Subject.h"
#include "SubjectComponent.h"

dae::ScoreComponent::ScoreComponent()
	: m_Score(0)
	, m_pSubjectComponent{ nullptr }
{
	
}

void dae::ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
	
	if (!m_pSubjectComponent)
		m_pSubjectComponent = m_pParent->GetComponent<SubjectComponent>();
	
	if (m_pSubjectComponent)
		m_pSubjectComponent->Notify(m_pParent, Event::playerScored);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}
