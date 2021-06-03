#include "QbertPCH.h"
#include "QBertApplication.h"

//General includes
#include "SceneManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "CustomUIRenderer.h"
#include "Structs.h"

//Components
#include "Components.h"
#include "GridComponent.h"
#include "GridPosition.h"

//Commands
#include "CustomCommands.h"

//Parsing
#include "rapidjson.h"
#include "document.h"
#include "fstream"


void QBertApplication::GameInitialize()
{
	Renderer::GetInstance().SetUIRenderer(new CustomUIRenderer{});
}

void QBertApplication::GameLoad() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1");
	auto objects = ParseLevel(scene, "Data/Level/Level1.json");
	
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

GameObject* QBertApplication::CreateGrid(Scene& scene, const glm::ivec2& gridPos, int gridWidth, int gridHeight, int cellSize, int steps, bool retrigger) const
{
	GameObject* grid = new GameObject{};
	GridComponent* gridComponent = new GridComponent{ gridPos, gridWidth, gridHeight, cellSize };
	gridComponent->SetNrOfTriggers(steps);
	gridComponent->RetriggerCells(retrigger);
	grid->AddComponent(new SubjectComponent{});
	grid->AddComponent(gridComponent);
	scene.Add(grid);
	return grid;
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

std::vector<GameObject*> QBertApplication::ParseLevel(Scene& scene, const std::string& filename) const
{
	GridComponent* pGrid = nullptr;
	std::vector<GameObject*> gameObjects{};
	
	std::ifstream stream{};
	stream.open(filename, std::ios::in);
	if (stream.is_open())
	{
		std::string json((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());
		rapidjson::Document doc;
		doc.Parse(json.c_str());

		//const rapidjson::Value& gameobjects = doc["gameobjects"];
		for (auto layerIt{ doc.Begin()}; layerIt < doc.End(); layerIt++)
		{
			const rapidjson::Value& layer = (*layerIt);
			const rapidjson::Value& object = layer["gameobjects"];

			for (auto objectIt{ object.Begin() }; objectIt < object.End(); objectIt++)
			{
				const rapidjson::Value& gameobject = *objectIt;
				std::string type = gameobject["type"].GetString();

				//Read grid from file
				if (type == "Grid")
				{
					int rows = gameobject["rows"].GetInt();
					int columns = gameobject["columns"].GetInt();
					int cellsize = gameobject["cellsize"].GetInt();
					int steps = gameobject["steps"].GetInt();
					bool retrigger = gameobject["retrigger"].GetBool();

					const glm::ivec2 gridPos{ int(GetWindowSize().x) / 2 - cellsize / 2, cellsize };
					auto grid = CreateGrid(scene, gridPos, rows, columns, cellsize, steps, retrigger);
					pGrid = grid->GetComponent<GridComponent>();
					gameObjects.push_back(grid);
					grid->SetTag("Grid");
				}
				//Read player from file
				else if (type == "Qbert")
				{
					if (pGrid)
					{
						int row = gameobject["row"].GetInt();
						int column = gameobject["column"].GetInt();
						SDL_Scancode leftup = SDL_Scancode(gameobject["leftup"].GetInt());
						SDL_Scancode leftdown = SDL_Scancode(gameobject["leftdown"].GetInt());
						SDL_Scancode rightup = SDL_Scancode(gameobject["rightup"].GetInt());
						SDL_Scancode rightdown = SDL_Scancode(gameobject["rightdown"].GetInt());
						int controllerId = gameobject["controllerId"].GetInt();

						MovementControls controls{ leftup, rightup, leftdown, rightdown };
						controls.ControllerId = controllerId;

						auto pQbert = CreateQbert(scene, pGrid, { row, column }, controls);
						gameObjects.push_back(pQbert);
					}
					else
					{
						std::cout << "Grid not initialized first in json file\n";
					}
				}
			}
		}
	}

	return gameObjects;
}
