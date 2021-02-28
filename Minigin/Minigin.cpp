#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Subject.h"
#include "Observer.h"

#include "Components.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"KayTee Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto goBackground = std::make_shared<GameObject>();
	auto goBackground = new GameObject();
	goBackground->AddComponent(new TextureComponent{"background.jpg"});
	scene.Add(goBackground);

	//auto goLogo = std::make_shared<GameObject>();
	auto goLogo = new GameObject();
	goLogo->GetComponent<Transform>()->SetPosition({ 216, 180, 0 });
	
	goLogo->AddComponent(new TextureComponent{ "logo.png" });
	scene.Add(goLogo);
	
	//auto goText = std::make_shared<GameObject>();
	auto goText = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	goText->GetComponent<Transform>()->SetPosition({ 80, 20, 0});
	goText->AddComponent(new TextureComponent{});
	goText->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	scene.Add(goText);

	//auto goFPSCounter = std::make_shared<GameObject>();
	auto goFPSCounter = new GameObject();
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	goFPSCounter->AddComponent(new TextureComponent{});
	goFPSCounter->AddComponent(new TextComponent{ "FPS:", fontFPS, {255, 255, 0} });
	goFPSCounter->AddComponent(new TimeComponent{});
	scene.Add(goFPSCounter);

	//auto goPlayer1 = std::make_shared<GameObject>();
	auto goPlayer1 = new GameObject();
	goPlayer1->AddComponent(new TextureComponent{});
	goPlayer1->AddComponent(new TextComponent{ "QBert HP: 5", fontFPS });
	goPlayer1->AddComponent(new HealthComponent{ 5 });
	goPlayer1->GetComponent<Transform>()->SetPosition(10, 180, 0);

	auto goScore1 = new GameObject();
	goScore1->AddComponent(new TextureComponent{});
	goScore1->AddComponent(new TextComponent{ "QBert Score: 0", fontFPS });
	goScore1->AddComponent(new ScoreComponent());
	goScore1->GetComponent<Transform>()->SetPosition(10, 220, 0);
	scene.Add(goScore1);

	Subject* subject = new Subject();
	Observer* playerObserver = new PlayerObserver{ goPlayer1, "QBert" , goScore1};
	subject->AddObserver(playerObserver);
	goPlayer1->SetSubject(subject);
	goScore1->SetSubject(subject);
	scene.Add(goPlayer1);
	
	auto goPlayer2 = new GameObject();
	goPlayer2->AddComponent(new TextureComponent{});
	goPlayer2->AddComponent(new TextComponent{ "P2 HP: 5", fontFPS });
	goPlayer2->AddComponent(new HealthComponent{ 5 });
	goPlayer2->GetComponent<Transform>()->SetPosition(10, 200, 0);

	auto goScore2 = new GameObject();
	goScore2->AddComponent(new TextureComponent{});
	goScore2->AddComponent(new TextComponent{ "P2 Score: 0", fontFPS });
	goScore2->AddComponent(new ScoreComponent());
	goScore2->GetComponent<Transform>()->SetPosition(10, 240, 0);
	scene.Add(goScore2);

	playerObserver = new PlayerObserver{ goPlayer2, "P2" , goScore2};
	subject->AddObserver(playerObserver);
	goPlayer2->SetSubject(subject);
	goScore2->SetSubject(subject);
	scene.Add(goPlayer2);
	scene.Add(subject);
	
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_P, InputType::released, new DamageCommand(goPlayer2));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_O, InputType::released, new DamageCommand(goPlayer1));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_1, InputType::held, new IncreaseScore(goScore1));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_2, InputType::held, new IncreaseScore(goScore2));
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		//while (doContinue)
		//{
		//	const auto currentTime = high_resolution_clock::now();
		//	
		//	doContinue = input.ProcessInput();
		//	sceneManager.Update();
		//	renderer.Render();
		//	
		//	auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
		//	this_thread::sleep_for(sleepTime);
		//}
		bool running = true;
		InputManager::GetInstance().AddCommand(SDL_SCANCODE_ESCAPE, InputType::released, new QuitCommand(&running));

		
		auto lastTime = std::chrono::high_resolution_clock::now();
		while(doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput() && running;
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
		
	}

	Cleanup();
}
