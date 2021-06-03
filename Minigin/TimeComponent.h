#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

class TimeComponent final : public BaseComponent
{
public:
	TimeComponent();
	virtual ~TimeComponent() = default;
	TimeComponent(const TimeComponent& other) = delete;
	TimeComponent(TimeComponent&& other) = delete;
	TimeComponent& operator=(const TimeComponent& other) = delete;
	TimeComponent& operator=(TimeComponent&& other) = delete;

	void Update(float dt) override;
	void Render() const override;

	int GetFPS() const;

private:
	int m_FPS;
	TextComponent* m_TextComponent;
	
};