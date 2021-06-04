#include "QbertPCH.h"
#include "CustomUIRenderer.h"
#include "imgui.h"

CustomUIRenderer::CustomUIRenderer()
	: m_LoadGamePressed(false)
{
}

void CustomUIRenderer::RenderUI()
{
	ImGui::Begin("Controls");
	m_LoadGamePressed = ImGui::Button("Test", { 50, 20 });
	ImGui::End();
}