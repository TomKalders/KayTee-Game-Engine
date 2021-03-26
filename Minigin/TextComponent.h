#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
//#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextureComponent;
	class TextElement;
	
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const glm::vec3& color = {255, 255, 255});
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float dt) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const glm::vec3& color);
		void SetTextElement(TextElement* textElement);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		glm::tvec3<uint8_t> m_Color;
		std::shared_ptr<Font> m_Font;
		TextElement* m_pHudElement;
	};
}

