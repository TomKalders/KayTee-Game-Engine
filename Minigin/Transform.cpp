#include "MiniginPCH.h"
#include "Transform.h"

Transform::Transform()
	: BaseComponent()
	, m_Position(glm::vec3{0, 0, 0})
{
}

Transform::Transform(const glm::vec3& position)
	: BaseComponent()
	, m_Position(position)
{
}

Transform::~Transform()
{
}

const glm::vec3& Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Transform::AddPosition(const glm::vec3& position)
{
	m_Position += position;
}

void Transform::AddPosition(float x, float y, float z)
{
	m_Position += glm::vec3{ x, y, z };
}

