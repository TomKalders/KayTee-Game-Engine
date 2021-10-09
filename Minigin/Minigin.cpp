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

void Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"KayTee Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowSize.x,
		m_WindowSize.y,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	HudManager::GetInstance().CreateHud();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem{});

	GameInitialize();
}

/**
 * Code constructing the scene world starts here
 */
void Minigin::LoadGame()
{
	GameLoad();
}

void Minigin::Cleanup()
{
	GameCleanup();
	Renderer::GetInstance().Destroy();
	HudManager::GetInstance().Destroy();
	ServiceLocator::DestroySoundService();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		
		auto lastTime = std::chrono::high_resolution_clock::now();
		while(doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput() && m_Running;
			GameUpdate(deltaTime);
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}
	Cleanup();
}

void Minigin::Quit()
{
	m_Running = false;
}

glm::ivec2 Minigin::GetWindowSize() const
{
	return m_WindowSize;
}
