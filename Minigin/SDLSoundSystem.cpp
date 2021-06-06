#include "MiniginPCH.h"
#include "SDL_mixer.h"
#include "SDLSoundSystem.h"

SDLSoundSystem::SDLSoundSystem()
	: m_SoundMutex{}
	, m_NextID{0}
	, m_IsRunning(true)
	, m_Thread(nullptr)
{
	CreateThread();
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_IsRunning = false;
	if (m_Thread->joinable())
		m_Thread->join();

	delete m_Thread;
	
	Mix_CloseAudio();
}

SoundID SDLSoundSystem::AddSound(const Sound& sound)
{
	std::lock_guard<std::mutex> soundLock{ m_SoundMutex };
	if (!DoesSoundExist(sound))
	{
		m_Sounds[m_NextID] = sound;
		++m_NextID;
		return m_NextID - 1;
	}
	else
		return GetSoundId(sound);
}

void SDLSoundSystem::Play(const SoundID id, const float volume)
{
	if (DoesSoundIdExist(id))
		AddToQueue(id, volume);
}

void SDLSoundSystem::CreateThread()
{
	if (!m_Thread)
	{
		m_Thread = new std::thread{
			[this]()
			{
				Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
				while (m_IsRunning)
				{
					std::lock_guard<std::mutex> soundLock{ m_SoundMutex };
					if (!m_SoundQueue.empty())
					{
						std::pair<SoundID, float> soundPair = m_SoundQueue.back();
						m_SoundQueue.pop();

						std::map<SoundID, Sound>::iterator sound = m_Sounds.find(soundPair.first);

						if (sound != m_Sounds.end())
						{
							Mix_Chunk* SDLSound{ Mix_LoadWAV(sound->second.path.c_str())};
							if (SDLSound)
							{
								SDLSound->volume = static_cast<Uint8>(soundPair.second);
								Mix_PlayChannel(-1, SDLSound, 0);
							}
						}
					}
				}
			}
		};
	}
}

void SDLSoundSystem::AddToQueue(SoundID id, float volume)
{
	std::lock_guard<std::mutex> soundLock{ m_SoundMutex };
	m_SoundQueue.push(std::pair<SoundID, float>(id, volume));
}

bool SDLSoundSystem::DoesSoundExist(const Sound& sound)
{
	auto it = std::find_if(m_Sounds.begin(), m_Sounds.end(), [sound](const std::pair<SoundID, Sound>& pair)
		{
			return pair.second.path == sound.path;
		}
	);

	if (it == m_Sounds.end())
		return false;

	return true;
}

bool SDLSoundSystem::DoesSoundIdExist(SoundID sound)
{
	return m_Sounds.find(sound) != m_Sounds.end();
}

SoundID SDLSoundSystem::GetSoundId(const Sound& sound)
{
	auto it = std::find_if(m_Sounds.begin(), m_Sounds.end(), [sound](const std::pair<SoundID, Sound>& pair)
		{
			return pair.second.path == sound.path;
		}
	);

	if (it != m_Sounds.end())
		return it->first;

	return 0;
}
