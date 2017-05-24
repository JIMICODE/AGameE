#include "SoundProcess.h"

SoundProcess::SoundProcess(std::shared_ptr<ResHandle> soundResource, int typeOfSound, int volume, bool looping)
{
	InitializeVolume();
}

SoundProcess::~SoundProcess()
{
	if (m_AudioBuffer)
	{
		//TO DO
	}
}
