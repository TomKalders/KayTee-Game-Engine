#include "QbertPCH.h"
#include "CustomUIRenderer.h"
#include "imgui.h"
#include "QBertApplication.h"

CustomUIRenderer::CustomUIRenderer(QBertApplication* pApp)
	: m_pApp(pApp)
{
}

void CustomUIRenderer::RenderUI()
{
	ImGui::Begin("Controls");
	if (ImGui::Button("Singleplayer"))
	{
		m_pApp->SetMode(Mode::normal);
		m_pApp->LoadFirstLevel();
	}
	if (ImGui::Button("Co-op"))
	{
		m_pApp->SetMode(Mode::coop);
		m_pApp->LoadFirstLevel();
	}
	if (ImGui::Button("Versus"))
	{
		m_pApp->SetMode(Mode::versus);
		m_pApp->LoadFirstLevel();
	}
	ImGui::End();
}