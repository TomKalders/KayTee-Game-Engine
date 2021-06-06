#pragma once
#include "UIRenderer.h"

class QBertApplication;
class CustomUIRenderer final : public UIRenderer
{
public:
	CustomUIRenderer(QBertApplication* pApp);
	virtual ~CustomUIRenderer() = default;
	CustomUIRenderer(const CustomUIRenderer& other) = delete;
	CustomUIRenderer(CustomUIRenderer&& other) noexcept = delete;
	CustomUIRenderer& operator=(const CustomUIRenderer& other) = delete;
	CustomUIRenderer& operator=(CustomUIRenderer&& other) = delete;

	void RenderUI() override;
private:
	QBertApplication* m_pApp;
};
