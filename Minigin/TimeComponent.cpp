#include "MiniginPCH.h"
#include "TimeComponent.h"
#include "GameObject.h"


TimeComponent::TimeComponent()
	: BaseComponent()
	, m_FPS{}
	, m_TextComponent(nullptr)
{
}

void TimeComponent::Update(float dt)
{
	if (!m_TextComponent)
		m_TextComponent = m_pParent->GetComponent<TextComponent>();

	m_FPS = int(1 / dt);
	
	if (m_TextComponent)
		m_TextComponent->SetText(std::to_string(m_FPS) + " FPS");
}

void TimeComponent::Render() const
{
	
}

int TimeComponent::GetFPS() const
{
	return m_FPS;
}
