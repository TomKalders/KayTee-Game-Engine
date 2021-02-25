#include "MiniginPCH.h"
#include "TimeComponent.h"
#include "GameObject.h"


dae::TimeComponent::TimeComponent()
	: BaseComponent()
	, m_FPS{}
	, m_TextComponent(nullptr)
{
}

void dae::TimeComponent::Update(float dt)
{
	if (!m_TextComponent)
		m_TextComponent = m_pParent->GetComponent<TextComponent>();

	m_FPS = int(1 / dt);
	
	if (m_TextComponent)
		m_TextComponent->SetText(std::to_string(m_FPS) + " FPS");
}

void dae::TimeComponent::Render() const
{
	
}

int dae::TimeComponent::GetFPS() const
{
	return m_FPS;
}
