#pragma once
#include "Singleton.h"
#include "Hud.h"


class HudManager final : public Singleton<HudManager>
{
public:
	void CreateHud()
	{
		if (!m_Hud)
			m_Hud = new Hud{};
	};
	
	Hud* GetHud()
	{
		if (!m_Hud)
			std::exception("Hud Not Initialized");
		
		return m_Hud;
	};

	void Destroy()
	{
		delete m_Hud;
	}
	
	void Update(float){};
	void Render(){};
private:
	friend class Singleton<HudManager>;
	HudManager() = default;
	Hud* m_Hud = nullptr;
};