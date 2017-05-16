#include "Sound.h"

using namespace std;

bool DirectSound_Init(HWND hwnd)
{
	//create DirectSound managet object
	pDSound = make_unique<CSoundManager>(new CSoundManager());
	//initialize DIrectSound
	HRESULT r = pDSound->Initialize(hwnd, DSSCL_PRIORITY);
	if (r != DS_OK)	
		return false;
	//set the primary buffer format
	r = pDSound->SetPrimaryBufferFormat(2, 22050, 16);
	if (r != DS_OK)
		return false;

	return true;
}

void DIrectSound_Shutdown()
{
}

std::shared_ptr<CSound> LoadSound(std::string filename)
{
	HRESULT r;
	//create local reference to wave data
	CSound *wave;
	//attempt to load the wave file
	wchar_t s[255];
	r = pDSound->Create(&wave, s);
	if (r != DS_OK)
		wave = NULL;

	//return the wave
	return shared_ptr<CSound>(wave);
}

void EPlaySound(std::shared_ptr<CSound> sound)
{
	sound->Play();
}

void ELoopSound(std::shared_ptr<CSound> sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void EStopSound(std::shared_ptr<CSound> sound)
{
	sound->Stop();
}
