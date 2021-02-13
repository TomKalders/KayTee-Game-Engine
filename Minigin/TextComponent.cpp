#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: BaseComponent()
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_pTextureComp(new TextureComponent())
{
}

dae::TextComponent::~TextComponent()
{
	delete m_pTextureComp;
	m_pTextureComp = nullptr;
}

void dae::TextComponent::Update(float dt)
{
	dt;
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
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
		m_pTextureComp->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_pTextureComp != nullptr)
	{
		m_pTextureComp->Render();
	}
}

void dae::TextComponent::SetParent(GameObject* pParent)
{
	BaseComponent::SetParent(pParent);
	m_pTextureComp->SetParent(pParent);
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
