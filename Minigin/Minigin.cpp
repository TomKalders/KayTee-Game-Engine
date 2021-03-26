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

#include "vld.h"

#include "Components.h"
#include "Hud.h"
#include "HudElements.h"
#include "HudManager.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

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
	HudManager::GetInstance().CreateHud();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem{});
	SDLSoundSystem* ss = static_cast<SDLSoundSystem*>(ServiceLocator::GetSoundSystem());
	SoundID id = ss->AddSound(Sound{ "../data/1up.wav" });
	ss->Play(id, 100);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//Create Scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background
	auto goBackground = new GameObject();
	goBackground->AddComponent(new TextureComponent{"background.jpg"});
	scene.Add(goBackground);

	//Logo
	auto goLogo = new GameObject();
	goLogo->GetComponent<Transform>()->SetPosition({ 216, 180, 0 });
	goLogo->AddComponent(new TextureComponent{ "logo.png" });
	scene.Add(goLogo);

	//Header Text
	auto goText = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	goText->GetComponent<Transform>()->SetPosition({ 80, 20, 0});
	goText->AddComponent(new TextureComponent{});
	goText->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	scene.Add(goText);

	//FPS Object
	auto goFPSCounter = new GameObject();
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	goFPSCounter->AddComponent(new TextureComponent{});
	goFPSCounter->AddComponent(new TextComponent{ "FPS:", fontFPS, {255, 255, 0} });
	goFPSCounter->AddComponent(new TimeComponent{});
	scene.Add(goFPSCounter);

	// - player 1
	auto goScore1 = new GameObject();
	auto goPlayer1 = new GameObject();
	glm::vec3 color = { 255, 255, 0 };
	
	//TextComponents
	TextComponent* scoreText = new TextComponent{ "Player 1 Score: 0", fontFPS };
	TextElement* textElement = new TextElement{ "Player 1 Score: 0", fontFPS, {10, 180}, color };
	scoreText->SetTextElement(textElement);
	goScore1->AddComponent(scoreText);
	HudManager::GetInstance().GetHud()->AddElement(textElement);

	TextComponent* healthText = new TextComponent{ "Player 1 HP: 0", fontFPS };
	textElement = new TextElement{ "Player 1 HP: 5", fontFPS, {10, 200}, color};
	healthText->SetTextElement(textElement);
	goScore1->AddComponent(healthText);
	HudManager::GetInstance().GetHud()->AddElement(textElement);

	//Observer
	ObserverComponent* playerObserverComponent = new ObserverComponent{ new PlayerObserver{ goPlayer1, "Player 1" } };
	goScore1->AddComponent(playerObserverComponent);
	scene.Add(goScore1);

	SubjectComponent* subjectComponent = new SubjectComponent{};
	subjectComponent->AddObserver(playerObserverComponent);
	goPlayer1->AddComponent(subjectComponent);
	goPlayer1->AddComponent(new TextureComponent{});
	goPlayer1->AddComponent(new HealthComponent{ 5 });
	goPlayer1->AddComponent(new ScoreComponent());
	scene.Add(goPlayer1);
	// - player 1

	// - player 2
	auto goScore2 = new GameObject();
	auto goPlayer2 = new GameObject();

	//TextComponents
	scoreText = new TextComponent{ "Player 2 Score: 0", fontFPS };
	textElement = new TextElement{ "Player 2 Score: 0", fontFPS, {10, 220}, color };
	scoreText->SetTextElement(textElement);
	goScore2->AddComponent(scoreText);
	HudManager::GetInstance().GetHud()->AddElement(textElement);

	healthText = new TextComponent{ "Player 2 HP: 5", fontFPS };
	textElement = new TextElement{ "Player 2 HP: 5", fontFPS, {10, 240}, color };
	healthText->SetTextElement(textElement);
	goScore2->AddComponent(healthText);
	HudManager::GetInstance().GetHud()->AddElement(textElement);

	//Observer
	playerObserverComponent = new ObserverComponent{ new PlayerObserver{ goPlayer2, "Player 2" } };
	goScore2->AddComponent(playerObserverComponent);
	scene.Add(goScore2);

	subjectComponent = new SubjectComponent{};
	subjectComponent->AddObserver(playerObserverComponent);
	goPlayer2->AddComponent(subjectComponent);
	goPlayer2->AddComponent(new TextureComponent{});
	goPlayer2->AddComponent(new HealthComponent{ 5 });
	goPlayer2->AddComponent(new ScoreComponent());
	scene.Add(goPlayer2);
	// - player 2

	//Input
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_P, InputType::released, new DamageCommand(goPlayer2));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_O, InputType::released, new DamageCommand(goPlayer1));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_1, InputType::held, new IncreaseScore(goPlayer1));
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_2, InputType::held, new IncreaseScore(goPlayer2));
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	HudManager::GetInstance().Destroy();
	ServiceLocator::DestroySoundService();
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
