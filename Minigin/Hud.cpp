#include "MiniginPCH.h"
#include "Hud.h"

Hud::Hud()
{
}

Hud::~Hud()
{
	for (BaseElement* element : m_Elements)
	{
		delete element;
		element = nullptr;
	}
}

void Hud::AddElement(BaseElement* element)
{
	m_Elements.push_back(element);
}

void Hud::Render()
{
	for (BaseElement* element : m_Elements)
	{
		element->Render();
	}
}