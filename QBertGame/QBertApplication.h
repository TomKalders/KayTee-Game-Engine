#pragma once
#include <Minigin.h>
#include "Scene.h"

struct MovementControls;
class GridComponent;
class QBertApplication final : public dae::Minigin
{
public:
	void GameInitialize() override;
	void GameLoad() const override;
	void GameCleanup() override;
	void GameUpdate(float deltaTime) override;

private:
	//Factories
	GameObject* CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const;

	//Helper Functions
	void AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls) const;
};


