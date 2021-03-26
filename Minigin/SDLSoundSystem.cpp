
#include "MiniginPCH.h"
#include "SDL_mixer.h"
#include "SDLSoundSystem.h"

dae::SDLSoundSystem::SDLSoundSystem()
	: m_SoundMutex{}
	, m_NextID{0}
{
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_CloseAudio();
}

dae::SoundID dae::SDLSoundSystem::AddSound(Sound sound)
{
	//std::lock_guard<std::mutex> soundLock{ m_SoundMutex };
	m_Sounds[m_NextID] = sound;
	++m_NextID;
	return m_NextID - 1;
}

void dae::SDLSoundSystem::Play(const SoundID id, const float volume)
{
	if (id < m_Sounds.size())
	{
		PlaySound(m_Sounds[id], volume);
	}
}

void dae::SDLSoundSystem::PlaySound(Sound sound, const float volume)
{
	//std::lock_guard<std::mutex> soundLock{ m_SoundMutex };
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	Mix_Chunk* SDLSound{ Mix_LoadWAV(sound.path.c_str()) };

	if (SDLSound)
	{
		SDLSound->volume = static_cast<Uint8>(volume);
		Mix_PlayChannel(-1, SDLSound, 0);
	}
}
