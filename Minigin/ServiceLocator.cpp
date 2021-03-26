#include "MiniginPCH.h"
#include "ServiceLocator.h"


dae::NullSoundSystem dae::ServiceLocator::m_NullSoundSystem{};
dae::SoundSystem* dae::ServiceLocator::m_pSoundSystem = &ServiceLocator::m_NullSoundSystem;

dae::ServiceLocator::ServiceLocator()
{
}

dae::ServiceLocator::~ServiceLocator()
{
}

void dae::ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	if (!soundSystem)
		m_pSoundSystem = &m_NullSoundSystem;
	
	DestroySoundService();
	m_pSoundSystem = soundSystem;
}

dae::SoundSystem* dae::ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystem)
		return m_pSoundSystem;

	return nullptr;
}

void dae::ServiceLocator::DestroySoundService()
{
	if (m_pSoundSystem && (m_pSoundSystem != &m_NullSoundSystem))
		delete m_pSoundSystem;
}
