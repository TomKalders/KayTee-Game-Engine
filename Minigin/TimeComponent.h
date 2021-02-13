#pragma once
#include "BaseComponent.h"

namespace dae
{
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
		float m_Time;
		int m_FPS;
		int m_Frames;
	};
}


