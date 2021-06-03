#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

class Texture2D;

class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const std::string& filename);
	TextureComponent(const std::string& filename, const glm::vec2& position);
	virtual ~TextureComponent() = default;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	void Update(float dt) override;
	void Render() const override;

	void SetTexture(const std::string& filename);
	void SetTexture(std::shared_ptr<Texture2D> texture);
	std::shared_ptr<Texture2D> GetTexture();

private:
	std::shared_ptr<Texture2D> m_spTexture;
	glm::vec2 m_Position;
	bool m_CustomPosition;
};