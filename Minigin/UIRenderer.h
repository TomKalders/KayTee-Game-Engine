#pragma once
class UIRenderer
{
public:
	UIRenderer();
	virtual ~UIRenderer() = default;
	UIRenderer(const UIRenderer& other) = delete;
	UIRenderer(UIRenderer&& other) = delete;
	UIRenderer& operator=(const UIRenderer& other) = delete;
	UIRenderer& operator=(UIRenderer&& other) = delete;

	virtual void RenderUI() = 0;
private:
	
};

