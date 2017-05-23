#include "SoundResource.h"
using namespace std;

bool WaveResourceLoader::ParseWave(char * wavStream, size_t length, std::shared_ptr<ResHandle> handle)
{
	shared_ptr<SoundResourceExtraData> extra = static_pointer_cast<SoundResourceExtraData>(handle->GetExtra());

	DWORD file = 0;
	DWORD fileEnd = 0;
	DWORD length = 0;
	DWORD type = 0;
	DWORD pos = 0;

	//mmioFOURCC-converts four chars into a 4 bute integer code.
	//The first 4 bytes of a valid .wav is 'R' , 'I' , 'F' , 'F'

	type = *((DWORD *)(wavStream + pos)); 
	pos += sizeof(DWORD);

	if (type != mmioFOURCC('R', 'I', 'F', 'F'))
		return false;

	length = *((DWORD*)(wavStream + pos));
	pos += sizeof(DWORD);
	type = *((DWORD*)(wavStream + pos));
	pos += sizeof(DWORD);

	//'W','A','V','E' for a legal .wav file
	if (type != mmioFOURCC('W', 'A', 'V', 'E'))
		return false; //not a wav

	//Find the end of the file
	fileEnd = length - 4;
	memset(&extra->m_WavFormatEx, 0, sizeof(WAVEFORMATEX));
	bool copiedBuffer = false;

	//Load the .wav format and the .wav data
	//Note that these blocks can be int either order
	while (file < fileEnd)
	{
		type = *((DWORD*)(wavStream + pos));
		pos += sizeof(DWORD);
		file += sizeof(DWORD);

		type = *((DWORD*)(wavStream + pos));
		pos += sizeof(DWORD);
		file += sizeof(DWORD);

		switch (type)
		{
		case mmioFOURCC('f', 'a', 'c', 't'):
		{
			MessageBox(nullptr, L"Warnning", L"We don't handle compressed wav files", NULL);
			break;
		}
		case mmioFOURCC('f', 'm', 't', ' '):
		{
			memcpy(&extra->m_WavFormatEx, wavStream + pos, length);
			pos += length;
			extra->m_WavFormatEx.cbSize = (WORD)length;
			break;
		}
		case mmioFOURCC('d', 'a', 't', 'a'):
		{
			copiedBuffer = true;
			if (length != handle->Size())
			{
				MessageBox(nullptr, L"Warnning", L"Wav resource size does not equal buffer size", NULL);
				return 0;
			}
			memcpy(handle->WritableBuffer(), wavStream + pos, length);
			pos += length;
			break;
		}
		}

		file += length;

		//If both blocks hace been seen, we can return true.
		if (copiedBuffer)
		{
			extra->m_LengthMilli = (handle->Size() * 1000) / extra->GetFormat()->nAvgBytesPerSec;
			return true;
		}

		//Increment the pointer past the block we just read,
		//and make sure the pointer is word alogned.
		if (length & 1)
		{
			++pos;
			++file;
		}
	}

	//If we get to here, the .wav file didn't contain all the right pieces.
	return false;
}
