#pragma once

enum class Event
{
	//Player Events
	playerDamaged,
	playerDied,
	playerScored,
	levelComplete
};

enum class SoundEvent
{
	play,
	pause,
	volumeUp,
	volumeDown,
	mute
};
