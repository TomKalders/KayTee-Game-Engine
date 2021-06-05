#pragma once
#include <Minigin.h>
#include "Scene.h"
#include "vld.h"

struct MovementControls;
class GridComponent;
class GridPosition;
class ObserverComponent;

class QBertApplication final : public Minigin
{
public:
	void GameInitialize() override;
	void GameLoad() override;
	void GameCleanup() override;
	void GameUpdate(float deltaTime) override;

	void LoadLevel(int levelNr);
	void LoadNextLevel();
private:
	//Factories
	GameObject* CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const;
	GameObject* CreateCoilly(Scene& scene, GridComponent* grid, GridPosition* playerPos, const glm::ivec2& coords);
	GameObject* CreateGrid(Scene& scene, const glm::ivec2& gridPos, int gridWidth, int gridHeight, int cellSize, int steps, bool retrigger) const;
	
	//Helper Functions
	void AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls) const;
	void CreateHudElement(GameObject* boundObject, const std::string& text, const glm::vec2& position, const glm::vec3& textColor = {1, 1, 1});
	std::vector<GameObject*> ParseLevel(Scene& scene, const std::string& filename);

	int m_CurrentLevel;
	int m_MaxLevel;
	bool m_LoadNextLevel;
};