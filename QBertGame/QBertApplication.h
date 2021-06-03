#pragma once
#include <Minigin.h>
#include "Scene.h"

struct MovementControls;
class GridComponent;
class ObserverComponent;

class QBertApplication final : public Minigin
{
public:
	void GameInitialize() override;
	void GameLoad() const override;
	void GameCleanup() override;
	void GameUpdate(float deltaTime) override;

private:
	//Factories
	GameObject* CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const;
	GameObject* CreateGrid(Scene& scene, const glm::ivec2& gridPos, int gridWidth, int gridHeight, int cellSize, int steps, bool retrigger) const;
	
	//Helper Functions
	void AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls) const;
	std::vector<GameObject*> ParseLevel(Scene& scene, const std::string& filename) const;

	ObserverComponent* m_GameObserver;
};