#include "QbertPCH.h"
#include "QBertApplication.h"

//Managers
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "HudManager.h"

//General includes
#include "Renderer.h"
#include "CustomUIRenderer.h"
#include "CustomObservers.h"
#include "Structs.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//Components
#include "Components.h"
#include "GridComponent.h"
#include "GridPosition.h"
#include "CoillyMoveComponent.h"
#include "SlickMoveComponent.h"

//Hud elements
#include "HudElements.h"

//Commands
#include "CustomCommands.h"

//Parsing
#include "rapidjson.h"
#include "document.h"
#include "fstream"


void QBertApplication::GameInitialize()
{
	srand(unsigned int(std::time(nullptr)));
	Renderer::GetInstance().SetUIRenderer(new CustomUIRenderer{this});
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem{});
	
	m_CurrentLevel = 1;
	m_MaxLevel = 4;
	m_LoadNextLevel = false;

	m_Mode = Mode::normal;
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
			LoadFirstLevel();
		else
		{
			LoadNextLevel();
			m_LoadNextLevel = false;
		}
	}
	if (m_PlayerDied)
	{
		m_PlayerDied = false;
		LoadFirstLevel();
	}
}

void QBertApplication::LoadLevel(int levelNr)
{
	SceneManager& sceneManager = SceneManager::GetInstance();
	std::string sceneName{ "Level" + std::to_string(levelNr) };
	sceneManager.RemoveScene(sceneName);
	Scene& scene = sceneManager.CreateScene(sceneName);

	SpawnSettings settings{};
	auto objects = ParseLevel(scene, "Data/Level/Level" + std::to_string(levelNr) + ".json", settings);
	SceneManager::GetInstance().SetActiveScene(sceneName);

	//Get Player coordinates and the grid
	GridComponent* pGrid{};
	for (GameObject* object : objects)
	{
		if (object->GetTag() == "Grid")
		{
			pGrid = object->GetComponent<GridComponent>();
		}
	}

	//Create Players
	GameObject* pPlayer1{};
	GameObject* pPlayer2{};

	MovementControls controlsP1{
		SDL_SCANCODE_A,
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_D
	};
	controlsP1.ControllerId = 1;
	MovementControls controlsP2{};
	
	switch (m_Mode)
	{
	case Mode::normal:
		pPlayer1 = CreateQbert(scene, pGrid, { 0, 0 }, controlsP1);
		break;

	case Mode::coop:
		pPlayer1 = CreateQbert(scene, pGrid, { 6, 0 }, controlsP1);
		pPlayer2 = CreateQbert(scene, pGrid, { 6, 6 }, controlsP2);
		break;

	case Mode::versus:
		pPlayer1 = CreateQbert(scene, pGrid, { 0, 0 }, controlsP1);
		pPlayer2 = CreateCoilly(scene, pGrid, pPlayer1, { 1, 0 }, controlsP2);
		break;
	}

	//Create Enemies
	if (pPlayer1 && pGrid)
	{
		if (settings.useCoilly)
			CreateCoilly(scene, pGrid, pPlayer1, pPlayer2, { 1, 0 });
		if (settings.useSlick)
			CreateSlick(scene, pGrid, pPlayer1, pPlayer2, { 1, 0 }, true);
		if (settings.useSam)
			CreateSlick(scene, pGrid, pPlayer1, pPlayer2, { 1, 0 }, false);
		if (settings.useWrongway)
			CreateUgg(scene, pGrid, pPlayer1, { pGrid->GetWidth() - 1, pGrid->GetHeight() - 1 }, false);
		if (settings.useUgg)
			CreateUgg(scene, pGrid, pPlayer1, { pGrid->GetWidth() - 1, 0 }, true);
	}

	//Create a new HUD
	HudManager::GetInstance().Destroy();
	HudManager::GetInstance().CreateHud();

	auto goPlayerStats = new GameObject();
	goPlayerStats->SetTag("HUD");
	glm::vec3 textColor = { 255, 255, 0 };

	//Create textcomponents for health and score, bind them to the HUD.
	CreateHudElement(goPlayerStats, "Lives: 3", { 10, 160 }, textColor);
	CreateHudElement(goPlayerStats, "Score: 0", { 10, 180 }, textColor);
	
	//Add observer to check if the health/score text has to be changed
	SubjectComponent* subject = nullptr;
	if (pPlayer1)
		subject = pPlayer1->GetComponent<SubjectComponent>();

	if (subject)
	{
		auto observer = new ObserverComponent{ new PlayerObserver{pPlayer1, m_PlayerDied} };
		goPlayerStats->AddComponent(observer);
		subject->AddObserver(observer);
	}

	subject = nullptr;
	if (pPlayer2)
		subject = pPlayer2->GetComponent<SubjectComponent>();

	if (subject)
	{
		auto observer = new ObserverComponent{ new PlayerObserver{pPlayer2, m_PlayerDied} };
		goPlayerStats->AddComponent(observer);
		subject->AddObserver(observer);
	}
	
	scene.Add(goPlayerStats);
}

void QBertApplication::LoadNextLevel()
{
	++m_CurrentLevel;
	LoadLevel(m_CurrentLevel);
}

void QBertApplication::LoadFirstLevel()
{
	m_CurrentLevel = 1;
	LoadLevel(m_CurrentLevel);
}

void QBertApplication::SetMode(const Mode& mode)
{
	m_Mode = mode;
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

GameObject* QBertApplication::CreateCoilly(Scene& scene, GridComponent* grid, GameObject* pPlayer1, GameObject* pPlayer2,const glm::ivec2& coords)
{
	GameObject* coilly = new GameObject{};
	coilly->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	coilly->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	coilly->AddComponent(new TextureComponent{ "Sprites/CoillyBall.png" });
	auto movement = new CoillyMoveComponent{ grid, pPlayer1, 1.5f };
	coilly->AddComponent(movement);

	if (pPlayer2)
		movement->SetPlayer2(pPlayer2);

	scene.Add(coilly);
	return coilly;
}

GameObject* QBertApplication::CreateCoilly(Scene& scene, GridComponent* grid, GameObject* pPlayer, const glm::ivec2& coords,
	const MovementControls& controls)
{
	GameObject* coilly = new GameObject{};
	coilly->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	coilly->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	coilly->AddComponent(new TextureComponent{ "Sprites/CoillyBall.png" });
	auto movement = new CoillyMoveComponent{ grid, pPlayer, 1 };
	coilly->AddComponent(movement);
	movement->IsPlayerControlled(true);
	scene.Add(coilly);

	AssignControls(coilly, grid, controls, true);
	
	return coilly;
}

GameObject* QBertApplication::CreateSlick(Scene& scene, GridComponent* grid, GameObject* pPlayer1, GameObject* pPlayer2,
                                          const glm::ivec2& coords, bool hasCoolGlasses)
{
	GameObject* sam = new GameObject{};
	sam->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	sam->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);
	SlickMoveComponent* movement;
	if (hasCoolGlasses)
	{
		sam->AddComponent(new TextureComponent{ "Sprites/Slick.png" });
		movement = new SlickMoveComponent{ grid, pPlayer1, 1.5f, 5.f, grid->GetWidth() - 1 };
	}
	else
	{
		sam->AddComponent(new TextureComponent{ "Sprites/Sam.png" });
		movement = new SlickMoveComponent{ grid, pPlayer1, 1.5f, 10.f, grid->GetWidth() - 1 };
	}
	if (pPlayer2)
		movement->SetPlayer2(pPlayer2);
	sam->AddComponent(movement);
	scene.Add(sam);
	return sam;
}

GameObject* QBertApplication::CreateUgg(Scene& scene, GridComponent* grid, GameObject* pPlayer,
	const glm::ivec2& coords, bool goingRight)
{
	GameObject* ugg = new GameObject{};
	ugg->AddComponent(new GridPosition{ coords });
	glm::vec2 position = grid->GetGridCenter(coords.x, coords.y);
	ugg->GetComponent<Transform>()->SetPosition(position.x, position.y, 0);

	SlickMoveComponent* movement;
	if (goingRight)
	{
		ugg->AddComponent(new TextureComponent{ "Sprites/Ugg.png" });
		movement = new SlickMoveComponent{ grid, pPlayer, 1.5f, 5.f, grid->GetWidth() - 1 };
		movement->SetMoveDirections({ {-1, 0}, {0, 1} });
	}
	else
	{
		ugg->AddComponent(new TextureComponent{ "Sprites/Wrongway.png" });
		movement = new SlickMoveComponent{ grid, pPlayer, 1.5f, 10.f, grid->GetWidth() - 1 };
		movement->SetMoveDirections({ {0, -1}, {-1, -1} });
	}
	movement->ReverseTiles(false);
	movement->HurtPlayer(true);
	ugg->AddComponent(movement);
	scene.Add(ugg);
	return ugg;
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

void QBertApplication::AssignControls(GameObject* player, GridComponent* grid, const MovementControls& controls, bool isEnemy) const
{
	InputManager::GetInstance().AddCommand(controls.RightUp, InputType::pressed, new MoveRightUp{ player, grid, isEnemy});
	InputManager::GetInstance().AddCommand(controls.LeftDown, InputType::pressed, new MoveLeftDown{ player, grid, isEnemy });
	InputManager::GetInstance().AddCommand(controls.RightDown, InputType::pressed, new MoveRightDown{ player, grid, isEnemy });
	InputManager::GetInstance().AddCommand(controls.LeftUp, InputType::pressed, new MoveLeftUp{ player, grid, isEnemy });

	InputManager::GetInstance().AddCommand(controls.ControllerRightUp, InputType::released, new MoveRightUp{ player, grid, isEnemy });
	InputManager::GetInstance().AddCommand(controls.ControllerLeftDown, InputType::released, new MoveLeftDown{ player, grid, isEnemy });
	InputManager::GetInstance().AddCommand(controls.ControllerRightDown, InputType::released, new MoveRightDown{ player, grid, isEnemy });
	InputManager::GetInstance().AddCommand(controls.ControllerLeftUp, InputType::released, new MoveLeftUp{ player, grid, isEnemy });
}

void QBertApplication::CreateHudElement(GameObject* boundObject, const std::string& text, const glm::vec2& position, const glm::vec3& textColor)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	TextComponent* healthText = new TextComponent{ text, font };
	TextElement* textElement = new TextElement{ text, font, position, textColor };
	healthText->SetTextElement(textElement);
	boundObject->AddComponent(healthText);
	HudManager::GetInstance().GetHud()->AddElement(textElement);
}

std::vector<GameObject*> QBertApplication::ParseLevel(Scene& scene, const std::string& filename, SpawnSettings& settings)
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
				else if (type == "Settings")
				{
					settings.useCoilly = gameobject["coilly"].GetBool();
					settings.useSam = gameobject["sam"].GetBool();
					settings.useSlick = gameobject["slick"].GetBool();
					settings.useUgg = gameobject["Ugg"].GetBool();
					settings.useWrongway = gameobject["wrongway"].GetBool();
				}
			}
		}
	}

	return gameObjects;
}
