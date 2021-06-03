#include "QbertPCH.h"
#include "QBertApplication.h"

//General includes
#include "SceneManager.h"
#include "InputManager.h"
#include "Structs.h"

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

	//Create the grid
	glm::ivec2 gridPos{ int(GetWindowSize().x) / 2 - cellSize / 2, cellSize };
	GameObject* grid = new GameObject{};
	GridComponent* gridComponent = new GridComponent{ gridPos, gridSize, gridSize, cellSize };
	grid->AddComponent(gridComponent);
	scene.Add(grid);

	//Create Player 1
	CreateQbert(scene, gridComponent, {6, 6}, MovementControls{});

	//Create Player 2
	MovementControls controls = MovementControls{
		SDL_SCANCODE_A,
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_D,
	};
	controls.ControllerId = 1;

	CreateQbert(scene, gridComponent, { 6, 0 },	controls);
}

void QBertApplication::GameCleanup()
{
}

void QBertApplication::GameUpdate(float)
{
}

GameObject* QBertApplication::CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const
{
	GameObject* qbert = new GameObject{};
	qbert->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	qbert->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	qbert->AddComponent(new TextureComponent{ "Sprites/Qbert.png" });
	scene.Add(qbert);

	AssignControls(qbert, grid, controls);

	return qbert;
}

void QBertApplication::AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls) const
{
	InputManager::GetInstance().AddCommand(controls.RightUp, InputType::pressed, new MoveRightUp{ player, grid });
	InputManager::GetInstance().AddCommand(controls.LeftDown, InputType::pressed, new MoveLeftDown{ player, grid });
	InputManager::GetInstance().AddCommand(controls.RightDown, InputType::pressed, new MoveRightDown{ player, grid });
	InputManager::GetInstance().AddCommand(controls.LeftUp, InputType::pressed, new MoveLeftUp{ player, grid });

	InputManager::GetInstance().AddCommand(controls.ControllerRightUp, InputType::released, new MoveRightUp{ player, grid });
	InputManager::GetInstance().AddCommand(controls.ControllerLeftDown, InputType::released, new MoveLeftDown{ player, grid });
	InputManager::GetInstance().AddCommand(controls.ControllerRightDown, InputType::released, new MoveRightDown{ player, grid });
	InputManager::GetInstance().AddCommand(controls.ControllerLeftUp, InputType::released, new MoveLeftUp{ player, grid });
}
