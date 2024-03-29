#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "BaseComponent.h"


	class Transform final: public BaseComponent
	{
	public:
		Transform();
		Transform(const glm::vec3& position);
		virtual ~Transform();

		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		void AddPosition(const glm::vec3& position);
		void AddPosition(float x, float y, float z);
	
	private:
		glm::vec3 m_Position;
	};