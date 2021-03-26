#pragma once

namespace dae
{
	enum class Event
	{
		//Player Events
		playerDamaged,
		playerDied,
		playerScored
		
	};

	enum class SoundEvent
	{
		play,
		pause,
		volumeUp,
		volumeDown,
		mute
	};
}