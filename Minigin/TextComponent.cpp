#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "HudElements.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const glm::vec3& color)
	: BaseComponent()
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Color(color)
	, m_Font(font)
{
}

void dae::TextComponent::Update(float dt)
{
	dt;
	if (m_NeedsUpdate)
	{
		TextureComponent* textureComponent = m_pParent->GetComponent<TextureComponent>();

		if (textureComponent)
		{
			const SDL_Color color = { m_Color.x, m_Color.y, m_Color.z };
			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			textureComponent->SetTexture(std::make_shared<Texture2D>(texture));
		}
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;

	if (m_pHudElement)
		m_pHudElement->SetText(text);
}

void dae::TextComponent::SetColor(const glm::vec3& color)
{
	m_Color = color;
}

void dae::TextComponent::SetTextElement(TextElement* textElement)
{
	m_pHudElement = textElement;
}
