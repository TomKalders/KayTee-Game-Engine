#pragma once
#include "Singleton.h"
#include "EventEnums.h"

namespace dae
{
	class SoundManager : public Singleton<SoundManager>
	{
	public:
		virtual ~SoundManager();
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) noexcept = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) = delete;

	private:
		friend class Singleton<SoundManager>;
		SoundManager() = default;

		
	};
}