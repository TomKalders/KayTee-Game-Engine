#include "QbertPCH.h"
#include "CustomUIRenderer.h"
#include "imgui.h"

CustomUIRenderer::CustomUIRenderer()
{
}

void CustomUIRenderer::RenderUI()
{
	ImGui::Begin("Controls");
	m_LoadGamePressed = ImGui::Button("Test", { 50, 20 });
	ImGui::End();
}