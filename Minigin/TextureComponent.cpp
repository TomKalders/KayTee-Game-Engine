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


dae::TextureComponent::TextureComponent()
	:BaseComponent()
{
}

dae::TextureComponent::TextureComponent(const std::string& filename)
	: BaseComponent()
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Update(float dt)
{
	dt;
}

void dae::TextureComponent::Render() const
{
	if (m_pParent && m_spTexture)
	{
		const auto pos = m_pParent->GetComponent<Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_spTexture = texture;
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()
{
	return m_spTexture;
}
