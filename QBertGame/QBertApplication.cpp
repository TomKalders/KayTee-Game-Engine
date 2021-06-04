#include "QbertPCH.h"
#include "QBertApplication.h"

//General includes
#include "SceneManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "CustomUIRenderer.h"
#include "CustomObservers.h"
#include "Structs.h"

//Components
#include "Components.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "CoillyMoveComponent.h"

//Commands
#include "CustomCommands.h"

//Parsing
#include "rapidjson.h"
#include "document.h"
#include "fstream"


void QBertApplication::GameInitialize()
{
	srand(unsigned int(std::time(nullptr)));
	Renderer::GetInstance().SetUIRenderer(new CustomUIRenderer{});
	m_CurrentLevel = 1;
	m_MaxLevel = 4;
	m_LoadNextLevel = false;
}

void QBertApplication::GameLoad()
{
	LoadLevel(m_CurrentLevel);
}

void QBertApplication::GameCleanup()
{
}

void QBertApplication::GameUpdate(float)
{
	if (m_LoadNextLevel)
	{
		if (m_CurrentLevel == m_MaxLevel - 1)
			Quit();
		else
		{
			LoadNextLevel();
			m_LoadNextLevel = false;
		}
	}
}

void QBertApplication::LoadLevel(int levelNr)
{
	std::string sceneName{ "Level" + std::to_string(levelNr) };
	Scene& scene = SceneManager::GetInstance().CreateScene(sceneName);
	auto objects = ParseLevel(scene, "Data/Level/Level" + std::to_string(levelNr) + ".json");
	SceneManager::GetInstance().SetActiveScene(sceneName);

	//Create Enemies
	GridPosition* playerPos{};
	GridComponent* pGrid{};
	for (GameObject* object : objects)
	{
		if (object->GetTag() == "")
		{
			playerPos = object->GetComponent<GridPosition>();
		}
		else if (object->GetTag() == "Grid")
		{
			pGrid = object->GetComponent<GridComponent>();
		}
	}

	if (playerPos && pGrid)
		CreateCoilly(scene, pGrid, playerPos, { 1, 0 });
}

void QBertApplication::LoadNextLevel()
{
	++m_CurrentLevel;
	LoadLevel(m_CurrentLevel);
}

GameObject* QBertApplication::CreateQbert(Scene& scene, GridComponent* grid, const glm::ivec2& coords, const MovementControls& controls) const
{
	GameObject* qbert = new GameObject{};
	qbert->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	qbert->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	qbert->AddComponent(new TextureComponent{ "Sprites/Qbert.png" });
	qbert->AddComponent(new SubjectComponent{});
	qbert->AddComponent(new HealthComponent{3});
	qbert->AddComponent(new ScoreComponent{});
	scene.Add(qbert);

	AssignControls(qbert, grid, controls);

	return qbert;
}

GameObject* QBertApplication::CreateCoilly(Scene& scene, GridComponent* grid, GridPosition* playerPos,const glm::ivec2& coords)
{
	GameObject* coilly = new GameObject{};
	coilly->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	coilly->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	coilly->AddComponent(new TextureComponent{ "Sprites/CoillyBall.png" });
	coilly->AddComponent(new CoillyMoveComponent{ grid, playerPos, 1});
	scene.Add(coilly);
	return coilly;
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

std::vector<GameObject*> QBertApplication::ParseLevel(Scene& scene, const std::string& filename)
{
	GridComponent* pGrid = nullptr;
	std::vector<GameObject*> gameObjects{};
	
	std::ifstream stream{};
	stream.open(filename, std::ios::in);
	if (stream.is_open())
	{
		std::string json((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());
		stream.close();
		
		rapidjson::Document doc;
		doc.Parse(json.c_str());

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

					//Add the observers & subjects
					GameObject* levelObserver{ new GameObject{} };
					levelObserver->SetTag("Observer");
					ObserverComponent* observer = new ObserverComponent{ new GridObserver{m_LoadNextLevel} };
					levelObserver->AddComponent(observer);

					auto subject = grid->GetComponent<SubjectComponent>();
					if (subject)
						subject->AddObserver(observer);
					
					scene.Add(levelObserver);
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

						GameObject* playerObserver = new GameObject{};
						playerObserver->SetTag("PlayerObserver");
						ObserverComponent* observer = new ObserverComponent{ new PlayerObserver{pQbert} };
						playerObserver->AddComponent(observer);
						
						auto subject = pQbert->GetComponent<SubjectComponent>();
						if (subject)
							subject->AddObserver(observer);
						
						scene.Add(playerObserver);
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
