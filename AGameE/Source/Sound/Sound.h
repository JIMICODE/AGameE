#pragma once
#ifndef SOUND_H_
#define SOUND_H_

#include"DirectSound.h"
#pragma comment(lib, "dsound.lib")
#include"..\Common\Utility.h"

class SoundSys
{
	friend class InitEngine;
private:
	std::unique_ptr<CSoundManager> m_pDSound;
	SoundSys() {}
	SoundSys(SoundSys& rhs) = delete;
	SoundSys operator= (SoundSys& rhs) = delete;
public:
	bool DirectSound_Init(HWND hwnd);
	void DirectSound_Shutdown();

	std::shared_ptr<CSound> LoadSound(std::string filename);
	void EPlaySound(std::shared_ptr<CSound> sound);
	void ELoopSound(std::shared_ptr<CSound> sound);
	void EStopSound(std::shared_ptr<CSound> sound);

	~SoundSys();
};
#endif // !SOUND_H_