#pragma once
#ifndef AUDIOBUFFER_H_
#define AUDIOBUFFER_H_

#include"..\Common\Utility.h"
#include"..\Resource\Resource.h"

class IAudioBuffer
{
public:
	virtual ~IAudioBuffer() {}

	virtual void *VGet() = 0;
	virtual std::shared_ptr<ResHandle> VGetResource() = 0;
	virtual bool VRestore() = 0;

	virtual bool VPlay(int volume, bool looping) = 0;
	virtual bool VPause() = 0;
	virtual bool VStop() = 0;
	virtual bool VResume() = 0;

	virtual bool VTogglePause() = 0;
	virtual bool VIssPlaying() = 0;
	virtual bool VIsLooping() const = 0;
	virtual void VSetVolume(int volume) = 0;
	virtual int VGetVolume() const = 0;
	virtual float VGetProgress() const = 0;
};

class AudioBuffer : public IAudioBuffer
{
public:
	virtual std::shared_ptr<ResHandle> VGetResource() override { return m_Resource; }
	virtual bool VIsLooping() const override { return m_isLooping; }
	virtual int VGetVolume() const override { return m_Volume; }
protected:
	std::shared_ptr<ResHandle> m_Resource;

	//Is the sound paused
	bool m_isPaused;

	//Is the sound looping
	bool m_isLooping;

	//the volume
	int m_Volume;
};

#endif // !AUDIOBUFFER_H_
