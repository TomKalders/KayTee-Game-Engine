#pragma once
#include "HudElements.h"

class Hud
{
public:
	Hud();
	~Hud();
	Hud(const Hud& other) = delete;
	Hud(Hud&& other) noexcept = delete;
	Hud& operator=(const Hud& other) = delete;
	Hud& operator=(Hud&& other) = delete;

	void AddElement(BaseElement* element);
	void Render();

	template <typename T>
	T* GetElement()
	{
		for (BaseElement* element : m_Elements)
		{
			T* castedPtr = dynamic_cast<T*>(element);
			if (castedPtr != nullptr)
			{
				return castedPtr;
			}
		}

		return nullptr;
	}
	
private:
	std::vector<BaseElement*> m_Elements;
};