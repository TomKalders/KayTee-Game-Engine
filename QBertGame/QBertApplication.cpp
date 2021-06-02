#include "QbertPCH.h"
#include "QBertApplication.h"

//General includes
#include "SceneManager.h"
#include "InputManager.h"
#include "SDL.h"

//Components
#include "Components.h"
#include "GridComponent.h"
#include "GridPosition.h"

//Commands
#include "CustomCommands.h"


void QBertApplication::GameInitialize()
{
}

void QBertApplication::GameLoad() const
{
	int gridSize = 7;
	int cellSize = 64;
	
	Scene& scene = SceneManager::GetInstance().CreateScene("Level");

	glm::ivec2 gridPos{ int(GetWindowSize().x) / 2 - cellSize / 2, cellSize };
	GameObject* grid = new GameObject{};
	GridComponent* gridComponent = new GridComponent{ gridPos, gridSize, gridSize, cellSize };
	grid->AddComponent(gridComponent);
	scene.Add(grid);

	auto qbert = CreateQbert(scene, gridComponent->GetGridCenter(0, 0));

	InputManager::GetInstance().AddCommand(SDL_SCANCODE_UP, InputType::released, new MoveRightUp{ qbert, gridComponent });
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_DOWN, InputType::released, new MoveLeftDown{ qbert, gridComponent });
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RIGHT, InputType::released, new MoveRightDown{ qbert, gridComponent });
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_LEFT, InputType::released, new MoveLeftUp{ qbert, gridComponent });
}

void QBertApplication::GameCleanup()
{
}

void QBertApplication::GameUpdate(float)
{
}

GameObject* QBertApplication::CreateQbert(Scene& scene, const glm::vec2& position) const
{
	GameObject* qbert = new GameObject{};
	qbert->AddComponent(new GridPosition{ {0, 0} });
	qbert->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	qbert->AddComponent(new TextureComponent{ "Sprites/Qbert.png" });
	scene.Add(qbert);
	return qbert;
}
