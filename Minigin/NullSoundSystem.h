#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final: public SoundSystem
	{
	public:
		NullSoundSystem();
		~NullSoundSystem();
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) noexcept = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;

		void Play(const SoundID id, const float volume) override;
	};
}