#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_

#include"DirectSound.h"
#pragma comment(lib, "dsound.lib")
#include"..\Common\Utility.h"
#include"AudioBuffer.h"
#include"..\Resource\Resource.h"

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

class IAudio
{
public:
	virtual bool VActice() = 0;

	virtual IAudioBuffer *VInitAudioBuffer(std::shared_ptr<ResHandle> soundResource) = 0;
	virtual void VReleaseAudioBuffer(IAudioBuffer *audioBuffer) = 0;

	virtual void VStopAllSounds() = 0;
	virtual void VPauseAllSounds() = 0;
	virtual void VResumeAllSounds() = 0;

	virtual bool VInitialize() = 0;
	virtual void VShutdown() = 0;
};

class Audio : public IAudio
{
public:
	Audio();
	virtual void VStopAllSounds() override;
	virtual void VPauseAllSounds() override;
	virtual void VResumeAllSounds() override;

	virtual void VShutdown() override;

	static bool HasSoundCard(void);
	bool IsPaused() { return m_AllPaused; }

protected:
	typedef std::list<IAudioBuffer*> AudioBufferList;
	AudioBufferList m_AllSamples; //List of all currently allocated buffers
	bool m_AllPaused; //Has the sound system been paused?
	bool m_Initialized; //Has the sound system been initialized?
};
#endif // !AUDIO_H_