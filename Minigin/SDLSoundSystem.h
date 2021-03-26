#pragma once
#include "SoundSystem.h"
#include <map>
#include <mutex>

namespace dae
{
	struct Sound
	{
		std::string path;
	};
	
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		SoundID AddSound(Sound sound);
		void Play(const SoundID id, const float volume) override;

	private:
		std::map<SoundID, Sound> m_Sounds;
		std::mutex m_SoundMutex;
		SoundID m_NextID;
		
		void PlaySound(Sound sound, const float volume);
	};
}