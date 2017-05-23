#pragma once
#ifndef SOUNDRESOURCE_H_
#define SOUNDRESOURCE_H_

#include"..\Resource\Resource.h"
#include"..\Common\Utility.h"

class WaveResourceLoader : public IResourceLoader
{
public:
	virtual bool VUseRawFile()override { return false; }
	virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize)override;
	virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle)override;
	virtual std::string VGetPattern()override { return "*.wav"; }

protected:
	bool ParseWave(char *wavStream, size_t length, std::shared_ptr<ResHandle> handle);
};

class OggReourceLoader : public IResourceLoader
{
public:
	virtual bool VUseRawFile()override { return false; }
	virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize)override;
	virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle)override;
	virtual std::string VGetPattern()override { return "*.ogg"; }

protected:
	bool ParseOgg(char *oggStream, size_t length, std::shared_ptr<ResHandle> handle);
};

class SoundResourceExtraData : public IResourceExtraData
{
	friend class WaveResourceLoader;
	friend class OggResourceLoader;

public:
	SoundResourceExtraData();
	virtual ~SoundResourceExtraData() {}

	virtual std::string VToString() { return "SoundResourceExtraData"; }

	enum SoundType GetSoundType() { return m_SoundType; }
	
	WAVEFORMATEX const *GetFormat() { return &m_WavFormatEx; }
	int GetLengthMilli() const { return m_LengthMilli; }

protected:
	enum SoundType m_SoundType;	//is this an ogg, Wav. etc.
	bool m_bInitialized;		//has ths sound been initialized
	WAVEFORMATEX m_WavFormatEx;	//description of the PCM format
	int m_LengthMilli;			//how long the sound is in milliseconds
	
};

#endif
