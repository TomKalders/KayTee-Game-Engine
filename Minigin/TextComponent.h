#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextureComponent;
	
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float dt) override;
		void Render() const override;

		void SetParent(GameObject* pParent) override;
		void SetText(const std::string & text);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		TextureComponent* m_pTextureComp;
	};
}

