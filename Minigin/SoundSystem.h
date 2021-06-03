#pragma once

using SoundID = unsigned short;
class SoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem();
	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) = delete;

	virtual void Play(const SoundID id, const float volume) = 0;
};