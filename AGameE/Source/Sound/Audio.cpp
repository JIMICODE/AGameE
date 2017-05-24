#include "Audio.h"

using namespace std;

void SoundSys::EPlaySound(std::shared_ptr<CSound> sound)
{
	sound->Play();
}

void SoundSys::ELoopSound(std::shared_ptr<CSound> sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void SoundSys::EStopSound(std::shared_ptr<CSound> sound)
{
	sound->Stop();
}

SoundSys::~SoundSys()
{
	DirectSound_Shutdown();
}

bool SoundSys::DirectSound_Init(HWND hwnd)
{
	//create DirectSound managet object
	m_pDSound = make_unique<CSoundManager>(new CSoundManager());
	//initialize DIrectSound
	HRESULT r = m_pDSound->Initialize(hwnd, DSSCL_PRIORITY);
	if (r != DS_OK)
		return false;
	//set the primary buffer format
	r = m_pDSound->SetPrimaryBufferFormat(2, 22050, 16);
	if (r != DS_OK)
		return false;

	return true;
}

void SoundSys::DirectSound_Shutdown()
{
}

std::shared_ptr<CSound> SoundSys::LoadSound(std::string filename)
{
	HRESULT r;
	//create local reference to wave data
	CSound *wave;
	//attempt to load the wave file
	wchar_t s[255];
	r = m_pDSound->Create(&wave, s);
	if (r != DS_OK)
		wave = NULL;

	//return the wave
	return shared_ptr<CSound>(wave);
}

void Audio::VShutdown()
{
	AudioBufferList::iterator i = m_AllSamples.begin();

	while (i != m_AllSamples.end())
	{
		IAudioBuffer *audioBuffer = (*i);
		audioBuffer->VStop();
		m_AllSamples.pop_front();
	}
}

//Stop all active sounds, including music
void Audio::VPauseAllSounds()
{
	AudioBufferList::iterator i = m_AllSamples.begin();
	AudioBufferList::iterator end = m_AllSamples.end();
	for (; i != end; ++i)
	{
		IAudioBuffer *audioBuffer = (*i);
		audioBuffer->VPause();
	}
	m_AllPaused = true;
}

void Audio::VResumeAllSounds()
{
	AudioBufferList::iterator i = m_AllSamples.begin();
	AudioBufferList::iterator end = m_AllSamples.end();

	for (; i != end; ++i)
	{
		IAudioBuffer *audioBuffer = (*i);
		audioBuffer->VResume();
	}
	m_AllPaused = false;
}

void Audio::VStopAllSounds()
{
	IAudioBuffer *audioBuffer = nullptr;

	AudioBufferList::iterator i = m_AllSamples.begin();
	AudioBufferList::iterator end = m_AllSamples.end();

	for (; i != end; ++i)
	{
		audioBuffer = (*i);
		audioBuffer->VStop();
	}

	m_AllPaused = false;

}
