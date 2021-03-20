#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "ObserverComponent.h"

namespace dae
{
	class SubjectComponent final : public BaseComponent
	{
	public:
		SubjectComponent();
		~SubjectComponent();
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) noexcept = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;

		void Update(float dt) override;
		void Render() const override;

		void AddObserver(ObserverComponent* observer);
		void RemoveObserver(ObserverComponent* observer);
		void Notify(GameObject* gameObject, Event event);
	
	private:
		std::vector<ObserverComponent*> m_Observers;
		Subject* m_pSubject = nullptr;
	};
}