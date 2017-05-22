#include "Sound.h"

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
