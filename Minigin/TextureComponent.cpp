#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture2D.h"
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"


TextureComponent::TextureComponent(const std::string& filename)
	: BaseComponent()
	, m_CustomPosition(false)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::TextureComponent(const std::string& filename, const glm::vec2& position)
	: BaseComponent()
	, m_Position(position)
	, m_CustomPosition(true)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::Update(float)
{
}

void TextureComponent::Render() const
{
	if (m_pParent && m_spTexture)
	{
		glm::vec3 pos = m_pParent->GetComponent<Transform>()->GetPosition();
		if (m_CustomPosition)
			pos = glm::vec3{ m_Position.x, m_Position.y, 0 };
		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_spTexture = texture;
}

std::shared_ptr<Texture2D> TextureComponent::GetTexture()
{
	return m_spTexture;
}
