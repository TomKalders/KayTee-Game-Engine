#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent()
	: m_pParent(nullptr)
{
	
}

dae::BaseComponent::BaseComponent(GameObject* parent)
	: m_pParent(parent)
{
}

dae::BaseComponent::~BaseComponent()
{
}

void dae::BaseComponent::Initialize()
{
}

void dae::BaseComponent::Update(float dt)
{
	dt;
}

void dae::BaseComponent::Render() const
{
}

void dae::BaseComponent::SetParent(GameObject* parent)
{
	m_pParent = parent;
}
