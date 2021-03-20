#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SubjectComponent;
	class ScoreComponent final : public BaseComponent
	{
	public:
		ScoreComponent();
		virtual ~ScoreComponent() = default;

		void AddScore(int amount);
		int GetScore() const;
	
	private:
		int m_Score;
		SubjectComponent* m_pSubjectComponent;
	};
}