#include "ResourceFile.h"

using namespace std;

ResHandle::ResHandle(Resource & resource, char * buffer, unsigned int size, ResCache * pResCache)
	: m_resource(resource)
{
	m_buffer = buffer;
	m_size = size;
	m_extra = nullptr;
	m_pResCache = pResCache;
}

ResHandle::~ResHandle()
{
	delete m_buffer;
	m_pResCache->MemoryHasBeenFreed(m_size);
}

std::shared_ptr<ResHandle> ResCache::Load(Resource * r)
{
	shared_ptr<IResourceLoader> loader;
	shared_ptr<ResHandle> handle;

	for (ResourceLoaders::iterator it = m_resourceLoaders.begin();
		it != m_resourceLoaders.end(); ++it)
	{
		shared_ptr<IResourceLoader> testLoader = *it;
		//if (WildcarMath(testLoader->VGetPattern().c_str(), r->m_name.c_str()))
		//{
		//	loader = testLoader;
		//	break;
		//}
	}

	if (!loader)
	{
		assert(loader && ("Default resource loader not found!"));
		return handle; //Resource not loaded!
	}

	unsigned int rawSize = m_file->VGetRawResourceSize(*r);
	char *rawBuffer = loader->VUseRawFile() ? Allocate(rawSize) : new char[rawSize];

	if (rawBuffer == nullptr)
	{
		//resource cache out of memory
		return shared_ptr<ResHandle>();
	}

	m_file->VGetRawResource(*r, rawBuffer);
	char *buffer = nullptr;
	unsigned int size = 0;

	if (loader->VUseRawFile())
	{
		buffer = rawBuffer;
		handle = shared_ptr<ResHandle>(new ResHandle(*r, buffer, rawSize, this));
	}
	else
	{
		size = loader->VGetLoadedResourceSize(rawBuffer, rawSize);
		buffer = Allocate(size);
		if (buffer == nullptr || rawBuffer  == nullptr)
		{
			//resource cache out of memory
			return shared_ptr<ResHandle>();
		}
		handle = shared_ptr<ResHandle>(new ResHandle(*r, buffer, size, this));
		bool success = loader->VLoadResource(rawBuffer, rawSize, handle);
		SAFE_DELETE_ARRAY(rawBuffer);

		if(!success)
		{
			//resourcecache out of memory
			return shared_ptr<ResHandle>();
		}
	}
	if(handle)
	{
		m_lru.push_front(handle);
		m_resources[r->m_name] = handle;
	}

	assert(loader && "Default resource loader not found");
	return handle;	//ResCache is out of memory
}

bool ResCache::MakeRoom(unsigned int size)
{
	if (size > m_cacheSize)
	{
		return false;
	}
	//return null if there's no possible wa yto allocate the memory
	while (size > (m_cacheSize - m_allocated))
	{
		//The cache is empty, and there's still not enough room
		if (m_lru.empty())
		{
			return false;
		}

		FreeOneResource();
	}

	return true;
}

char * ResCache::Allocate(unsigned int size)
{
	if (!MakeRoom(size))
		return nullptr;

	char *mem = new char[size];
	if (mem)
		m_allocated += size;

	return mem;
}

void ResCache::FreeOneResource()
{
	ResHandleList::iterator gonner = m_lru.end();
	gonner--;

	shared_ptr<ResHandle> handle = *gonner;

	m_lru.pop_back();
	m_resources.erase(handle->m_resource.m_name);
}

ResCache::ResCache(const unsigned int sizeInMb, IResourceFile * resFile)
{
	m_cacheSize = sizeInMb * 1024 * 1024;	//total memory size
	m_allocated = 0; //total memory allocated
	m_file = resFile;
}

ResCache::~ResCache()
{
	while (!m_lru.empty())
	{
		FreeOneResource();
	}
	SAFE_DELETE(m_file);
}

bool ResCache::Init()
{
	bool retValue = false;
	if (m_file->VOpen())
	{
		RegisterLoader(shared_ptr<IResourceLoader>(new DefaultResourceLoader()));
		retValue = true;
	}
	return retValue;
}

std::shared_ptr<ResHandle> ResCache::GetHandle(Resource * r)
{
	shared_ptr<ResHandle> handle(Find(r));

	if (handle == NULL)
		handle = Load(r);
	else
		Update(handle);

	return handle;
}
