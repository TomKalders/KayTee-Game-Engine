#pragma once
#include <iostream>
#include "GameObject.h"
#include "Components.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

namespace dae
{
	class Command
	{
	public:
		Command();
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};

	class FireCommand final : public Command
	{
	public:
		FireCommand() {};
		void Execute() override { std::cout << "Fire...\n"; };
	};

	class JumpCommand final : public Command
	{
	public:
		JumpCommand() {};
		void Execute() override { std::cout << "Jump...\n"; };
	};

	class DriveCommand final : public Command
	{
	public:
		DriveCommand() {};
		void Execute() override { std::cout << "Drive...\n"; };
	};

	class BananaCommand final : public Command
	{
	public:
		BananaCommand() {};
		void Execute() override { std::cout << "Banana...\n"; };
	};

	class QuitCommand final : public Command
	{
	public:
		QuitCommand(bool* quit) { m_ShouldQuit = quit; };
		void Execute() override { *m_ShouldQuit = !(*m_ShouldQuit); };
	private:
		bool* m_ShouldQuit;
	};


	class DamageCommand final : public Command
	{
	public:
		DamageCommand(GameObject* gameObject) { m_GameObject = gameObject; };
		void Execute() override
		{
			HealthComponent* health = m_GameObject->GetComponent<HealthComponent>();
			health->Damage(1);
		};
	
	private:
		GameObject* m_GameObject;
	};

	class IncreaseScore final : public Command
	{
	public:
		IncreaseScore(GameObject* gameObject) { m_GameObject = gameObject; };
		void Execute() override
		{
			ScoreComponent* score = m_GameObject->GetComponent<ScoreComponent>();
			score->AddScore(500);
		};

	private:
		GameObject* m_GameObject;
	};

	class PlaySound final : public Command
	{
	public:
		PlaySound(Sound sound)
		{
			m_SoundSystem = static_cast<SDLSoundSystem*>(ServiceLocator::GetSoundSystem());
			if (m_SoundSystem)
				m_Id = m_SoundSystem->AddSound(sound);
		};
		void Execute() override
		{
			m_SoundSystem->Play(m_Id, 100.f);
		};

	private:
		SDLSoundSystem* m_SoundSystem;
		SoundID m_Id;
	};
}