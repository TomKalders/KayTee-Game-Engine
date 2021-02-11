#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
	: BaseComponent()
	, m_Position(glm::vec3{0, 0, 0})
{
}

dae::Transform::Transform(const glm::vec3& position)
	: BaseComponent()
	, m_Position(position)
{
}

dae::Transform::~Transform()
{
}

const glm::vec3& dae::Transform::GetPosition() const
{
	return m_Position;
}

void dae::Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void dae::Transform::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

//void dae::Transform::SetPosition(const glm::vec2& position)
//{
//	m_Position = glm::vec3{ position, m_Position.z };
//}
