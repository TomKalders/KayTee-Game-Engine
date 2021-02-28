#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent()
	: m_Score(0)
{
}

void dae::ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
	m_pParent->GetSubject()->Notify(m_pParent, Event::playerScored);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}
