#pragma once
#ifndef RESOURCE_H_
#define RESOURCE_H_

#include"..\Common\Utility.h"

class IResourceFile
{
public:
	virtual bool VOpen() = 0;
	virtual int VGetRawResourceSize(const Resource &r) = 0;
	virtual int VGetRawResource(const Resource &r, char *buffer) = 0;
	virtual int VGetNumResources()const = 0;
	virtual std::string VGetResourceName(int num)const = 0;
	virtual ~IResourceFile() {}
};

class IResourceExtraData
{

};

class ResHandle
{
	friend class ResCache;

protected:
	Resource m_resource;
	char *m_buffer;
	unsigned int m_size;
	std::shared_ptr<IResourceExtraData> m_extra;
	ResCache *m_pResCache;

public:
	ResHandle::ResHandle(Resource &resource, char *buffer, unsigned int size, ResCache *pResCache)
		: m_resource(resource)
	{
		m_buffer = buffer;
		m_size = size;
		m_extra = nullptr;
		m_pResCache = pResCache;
	}
	virtual ~ResHandle();

	unsigned int Size() const { return m_size; }
	char *Buffer() const { return m_buffer; }
	char *WritableBuffer() { return m_buffer; }
	std::shared_ptr<IResourceExtraData> GetExtra() { return m_extra; }
	void SetExtra(std::shared_ptr<IResourceExtraData> extra) { m_extra = extra; }
};

class IResourceLoader
{
public:
	virtual std::string VGetPattern() = 0;
	virtual bool VUseRawFile() = 0;
	virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize) = 0;
	virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle) = 0;
};

class DefaultResourceLoader : public IResourceLoader
{
public:
	virtual bool VUseRawFile() override { return true; }
	virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize) override { return rawSize; }
	virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResHandle> handle) override
	{
		return true;
	}

	virtual std::string VGetPattern()override { return "*"; }
};

typedef std::list<std::shared_ptr<ResHandle>> ResHandleList;
typedef std::map<std::string, std::shared_ptr<ResHandle>> ResHandleMap;
typedef std::list<std::shared_ptr<IResourceLoader>> ResourceLoaders;

class ResCache
{
protected:
	ResHandleList m_lru; //LRU (least recently used> list
	ResHandleMap m_resources; //STL map for map resource lookup
	ResourceLoaders m_resourceLoaders; 

	IResourceFile *m_file; //Object that implements IResouceFile

	unsigned int m_cacheSize; //total memory size
	unsigned int m_allocated; //total memory allocated

	std::shared_ptr<ResHandle> Find(Resource *r);
	const void *Update(std::shared_ptr<ResHandle> handle);
	std::shared_ptr<ResHandle> Load(Resource *r);
	void Free(std::shared_ptr<ResHandle> gonner);

	bool MakeRoom(unsigned int size);
	char *Allocate(unsigned int size);
	void FreeOneResource();

public:
	ResCache(const unsigned int sizeInMb, IResourceFile *resFile);
	~ResCache();

	bool Init();
	void RegisterLoader(std::shared_ptr<IResourceLoader> loader);

	std::shared_ptr<ResHandle> GetHandle(Resource *r);
	int Preload(const std::string pattern, void(*progressCallback)(int, bool &));
	void Flush();

	void MemoryHasBeenFreed(unsigned int size);
};

class Resource
{
public:
	std::string m_name;
	Resource(const std::string &name)
	{
		m_name = name;
	}
};
#endif // !RESOURCE_H_
