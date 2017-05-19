#pragma once
#ifndef RESOURCEFILE_H_
#define RESOURCEFILE_H_

#include"Resource.h"

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
	ResHandle(Resource &resource, char *buffer, unsigned int size, ResCache *pResCache);
	virtual ~ResHandle();

	unsigned int Size() const { return m_size; }
	char *Buffer() const { return m_buffer; }
	char *WritableBuffer() { return m_buffer; }
	std::shared_ptr<IResourceExtraData> GetExtra() { return m_extra; }
	void SetExtra(std::shared_ptr<IResourceExtraData> extra) { m_extra = extra; }
};


#endif // !RESOURCEFILE_H_
