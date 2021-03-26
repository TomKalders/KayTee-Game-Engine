#pragma once
#include "SoundSystem.h"
#include "NullSoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		ServiceLocator();
		~ServiceLocator();
		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) noexcept = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;

		static void RegisterSoundSystem(SoundSystem* soundSystem);
		static SoundSystem* GetSoundSystem();
		static void DestroySoundService();
	
	private:
		static SoundSystem* m_pSoundSystem;
		static NullSoundSystem m_NullSoundSystem;

	};
}