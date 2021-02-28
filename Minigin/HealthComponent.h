﻿#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(int health);
		~HealthComponent();

		void Update(float dt) override;
		void Render() const override;

		void Damage(int damage);
		void Heal(int health);

		int GetHealth();
		void SetHealth(int health);

	private:
		int m_Health;
		int m_MaxHealth;
	};
}
