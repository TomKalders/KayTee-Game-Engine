#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent()
	: m_pParent(nullptr)
{
	
}

BaseComponent::BaseComponent(GameObject* parent)
	: m_pParent(parent)
{
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::Initialize()
{
}

void BaseComponent::Update(float dt)
{
	dt;
}

void BaseComponent::Render() const
{
}

void BaseComponent::SetParent(GameObject* parent)
{
	m_pParent = parent;
}
