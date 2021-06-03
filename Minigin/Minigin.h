#pragma once
struct SDL_Window;
namespace dae
{
	class Hud;
	class Minigin
	{
	public:
		virtual void GameInitialize() = 0;
		virtual void GameLoad() const = 0;
		virtual void GameCleanup() = 0;
		virtual void GameUpdate(float deltaTime) = 0;
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		void Quit();
		glm::ivec2 GetWindowSize() const;
		
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		glm::ivec2 m_WindowSize{640, 480};
		bool m_Running = true;
	};
}