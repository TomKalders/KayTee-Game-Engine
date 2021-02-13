#pragma once
//#include "GameObject.h"

namespace dae
{
	class GameObject;
	
	class BaseComponent
	{
	public:
		BaseComponent();
		BaseComponent(GameObject* parent);
		virtual ~BaseComponent();

		virtual void Update(float dt);
		virtual void Render() const;

		virtual void SetParent(GameObject* pParent);
	
	protected:
		GameObject* m_pParent;
	};
}