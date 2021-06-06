#pragma once
#include <Minigin.h>
#include "Scene.h"
#include "vld.h"

struct MovementControls;
class GridComponent;
class GridPosition;
class ObserverComponent;

struct SpawnSettings
{
	bool useCoilly;
	bool useSam;
	bool useSlick;
	bool useUgg;
	bool useWrongway;
};

enum class Mode
{
	normal,
	coop,
	versus
};

class QBertApplication final : public Minigin
{
public:
	void GameInitialize() override;
	void GameLoad() override;
	void GameCleanup() override;
	void GameUpdate(float deltaTime) override;

	void LoadLevel(int levelNr);
	void LoadNextLevel();
	void LoadFirstLevel();
	void SetMode(const Mode& mode);

private:
	//GameObject Creators
	GameObject* CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const;
	GameObject* CreateCoilly(Scene& scene, GridComponent* grid, GameObject* pPlayer1, GameObject* pPlayer2, const glm::ivec2& coords);
	GameObject* CreateCoilly(Scene& scene, GridComponent* grid, GameObject* pPlayer, const glm::ivec2& coords, const MovementControls& controls);
	GameObject* CreateSlick(Scene& scene, GridComponent* grid, GameObject* pPlayer1, GameObject* pPlayer2, const glm::ivec2& coords, bool hasCoolGlasses);
	GameObject* CreateUgg(Scene& scene, GridComponent* grid, GameObject* pPlayer, const glm::ivec2& coords, bool goingRight);
	GameObject* CreateGrid(Scene& scene, const glm::ivec2& gridPos, int gridWidth, int gridHeight, int cellSize, int steps, bool retrigger) const;
	
	//Helper Functions
	void AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls, bool isEnemy = false) const;
	void CreateHudElement(GameObject* boundObject, const std::string& text, const glm::vec2& position, const glm::vec3& textColor = {1, 1, 1});
	std::vector<GameObject*> ParseLevel(Scene& scene, const std::string& filename, SpawnSettings& settings);
	
	int m_CurrentLevel;
	int m_MaxLevel;
	bool m_LoadNextLevel;
	bool m_PlayerDied;

	Mode m_Mode;
};