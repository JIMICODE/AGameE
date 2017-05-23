#include "SoundResource.h"
using namespace std;

bool WaveResourceLoader::ParseWave(char * wavStream, size_t length, std::shared_ptr<ResHandle> handle)
{
	shared_ptr<SoundResourceExtraData> extra = static_pointer_cast<SoundResourceExtraData>(handle->GetExtra());
}
