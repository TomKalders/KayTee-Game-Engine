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
		"Programming 4 assignment",
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

	auto goBackground = std::make_shared<GameObject>();
	goBackground->AddComponent(new TextureComponent{"background.jpg"});
	scene.Add(goBackground);

	auto goLogo = std::make_shared<GameObject>();
	goLogo->GetComponent<Transform>()->SetPosition({ 216, 180, 0 });
	
	goLogo->AddComponent(new TextureComponent{ "logo.png" });
	scene.Add(goLogo);
	
	auto goText = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	goText->GetComponent<Transform>()->SetPosition({ 80, 20, 0});
	goText->AddComponent(new TextureComponent{});
	goText->AddComponent(new TextComponent{ "Programming 4 Assignment", font });
	scene.Add(goText);

	auto goFPSCounter = std::make_shared<GameObject>();
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	goFPSCounter->AddComponent(new TextureComponent{});
	goFPSCounter->AddComponent(new TextComponent{ "FPS:", fontFPS, {255, 255, 0} });
	goFPSCounter->AddComponent(new TimeComponent{});
	scene.Add(goFPSCounter);
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

		auto lastTime = std::chrono::high_resolution_clock::now();
		while(doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
		
	}

	Cleanup();
}
