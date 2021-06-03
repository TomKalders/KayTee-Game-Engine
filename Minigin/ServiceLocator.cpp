#include "MiniginPCH.h"
#include "ServiceLocator.h"


NullSoundSystem ServiceLocator::m_NullSoundSystem{};
SoundSystem* ServiceLocator::m_pSoundSystem = &ServiceLocator::m_NullSoundSystem;

ServiceLocator::ServiceLocator()
{
}

ServiceLocator::~ServiceLocator()
{
}

void ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	if (!soundSystem)
		m_pSoundSystem = &m_NullSoundSystem;
	
	DestroySoundService();
	m_pSoundSystem = soundSystem;
}

SoundSystem* ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystem)
		return m_pSoundSystem;

	return nullptr;
}

void ServiceLocator::DestroySoundService()
{
	if (m_pSoundSystem && (m_pSoundSystem != &m_NullSoundSystem))
		delete m_pSoundSystem;
}
