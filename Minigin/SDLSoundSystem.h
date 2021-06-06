#pragma once
#include "SoundSystem.h"
#include <map>
#include <mutex>
#include <queue>
#include <thread>

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

	SoundID AddSound(const Sound& sound);
	void Play(const SoundID id, const float volume) override;

private:
	std::map<SoundID, Sound> m_Sounds;
	std::mutex m_SoundMutex;
	SoundID m_NextID;
	
	std::thread* m_Thread;
	std::queue<std::pair<SoundID, float>> m_SoundQueue;
	bool m_IsRunning;

	void CreateThread();
	void AddToQueue(SoundID id, float volume);
	bool DoesSoundExist(const Sound& sound);
	bool DoesSoundIdExist(SoundID sound);
	SoundID GetSoundId(const Sound& sound);
};
