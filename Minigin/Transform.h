#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "BaseComponent.h"

namespace dae
{
	class Transform : public BaseComponent
	{
	public:
		Transform();
		Transform(const glm::vec3& position);
		virtual ~Transform();
		
		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		//void SetPosition(const glm::vec2& position);
	private:
		glm::vec3 m_Position;
	};
}
