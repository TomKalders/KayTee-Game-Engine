#pragma once
#include <Minigin.h>
#include "Scene.h"

class GridComponent;
class QBertApplication final : public dae::Minigin
{
public:
	void GameInitialize() override;
	void GameLoad() const override;
	void GameCleanup() override;
	void GameUpdate(float deltaTime) override;

private:
	
	GameObject* CreateQbert(Scene& scene, const glm::vec2& position) const;
};


