#include "MiniginPCH.h"
#include "Hud.h"

dae::Hud::Hud()
{
}

dae::Hud::~Hud()
{
	for (BaseElement* element : m_Elements)
	{
		delete element;
		element = nullptr;
	}
}

void dae::Hud::AddElement(BaseElement* element)
{
	m_Elements.push_back(element);
}

void dae::Hud::Render()
{
	for (BaseElement* element : m_Elements)
	{
		element->Render();
	}
}