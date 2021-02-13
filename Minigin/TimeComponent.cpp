#include "MiniginPCH.h"
#include "TimeComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::TimeComponent::TimeComponent()
	: BaseComponent()
{
}

void dae::TimeComponent::Update(float dt)
{
	m_Frames++;
	m_Time += dt;

	if (m_Time > 1.f)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_Time = 0;
		
		TextComponent* text = m_pParent->GetComponent<TextComponent>();
		if (text)
		{
			text->SetText(std::to_string(m_FPS) + " FPS");
		}
	}
}

void dae::TimeComponent::Render() const
{
	
}

int dae::TimeComponent::GetFPS() const
{
	return m_FPS;
}
