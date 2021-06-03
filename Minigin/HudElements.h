#pragma once
#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#pragma warning(push)
#pragma warning (disable:4201)
//#include <glm/vec3.hpp>
#include <glm/glm.hpp>
//#include "glm/vec2.hpp"
#pragma warning(pop)

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"


class BaseElement
{
public:
	BaseElement() = default;
	virtual ~BaseElement(){};
	BaseElement(const BaseElement& other) = delete;
	BaseElement(BaseElement&& other) = delete;
	BaseElement& operator=(const BaseElement& other) = delete;
	BaseElement& operator=(BaseElement&& other) = delete;

	virtual void Render() = 0;
private:
};

class TextElement final : public BaseElement
{
public:
	TextElement(const std::string& text, const std::shared_ptr<Font>& font, const glm::vec2& position = { 0, 0 }, const glm::vec3& color = { 255, 255, 255 })
		: m_Text{ text }
		, m_Position(position)
		, m_Font(font)
		, m_Color(color)
		, m_NeedsUpdate(true)
		, m_spTexture{ nullptr }
	{
		
	};
	
	void Render() override
	{
		if (m_NeedsUpdate)
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
			m_spTexture = std::make_shared<Texture2D>(texture);
			m_NeedsUpdate = false;
		}

		Renderer::GetInstance().RenderTexture(*m_spTexture, m_Position.x, m_Position.y);
	};

	void SetText(const std::string& text)
	{
		m_NeedsUpdate = true;
		m_Text = text;
	}

	void SetColor(const glm::vec3& color)
	{
		m_Color = color;
	}

private:
	std::shared_ptr<Font> m_Font;
	std::string m_Text;
	glm::vec2 m_Position;
	glm::tvec3<uint8_t> m_Color;
	std::shared_ptr<Texture2D> m_spTexture;
	bool m_NeedsUpdate;
};