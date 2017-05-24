#pragma once
#ifndef SOUNDPROCESS_H_

#include"Process.h"
#include"..\Common\Utility.h"
#include"..\Resource\Resource.h"
#include"..\Sound\AudioBuffer.h"

class SoundProcess : public Process
{
public:
	SoundProcess(
		std::shared_ptr<ResHandle> soundResource,
		int typeOfSound = PROC_SOUNDFX,
		int volume = 100,
		bool looping = false);

	virtual ~SoundProcess();

	virtual void VOnUpdate(const Timer& timer)override;
	virtual void VOnInitialize();
	virtual void VKill();
	
	virtual void VTogglePause();

	void SetVolume(int volume);
	int GetVolume();
	int GetLengthMilli();
	bool IsSoundVaild() { return m_SoundResource != nullptr; }
	bool IsPlaying();
	bool IsLooping() { return m_AudioBuffer->VIsLooping(); }
	float GetProgress();
	
protected:
	SoundProcess(); //Disable Default Construction

	void InitializeVolume();
	void Replay() { m_bInitialUpdate = true; }

	std::shared_ptr<ResHandle> m_SoundResource;
	std::shared_ptr<IAudioBuffer> m_AudioBuffer;

	int m_Volume;
	bool m_isLooping;

	bool m_bInitialUpdate;
};

#endif // !SOUNDPROCESS_H_
