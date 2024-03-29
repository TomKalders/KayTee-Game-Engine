﻿#pragma once
#include "BaseComponent.h"

class TextComponent;
class SubjectComponent;

class HealthComponent : public BaseComponent
{
public:
	HealthComponent(int health);
	~HealthComponent();

	void Update(float dt) override;
	void Render() const override;

	void Damage(int damage);
	void Heal(int health);

	int GetHealth() const;
	void SetHealth(int health);

	bool IsDead();

private:
	int m_Health;
	int m_MaxHealth;
	SubjectComponent* m_pSubjectComponent;
};

