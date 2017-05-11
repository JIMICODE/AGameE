#pragma once
#ifndef ACTORCOMPONENT_H_
#define ACTORCOMPONENT_H_

class ActorComponent
{
	friend class ActorFactory;
protected:
	StrongActorPtr mpOwner;

public:
	virtual ~ActorComponent() {}

	//These functions are meants to be overridden by the implementation
	//classes of the component.
	virtual bool VInit(TiXmlElement* pData) = 0;
	virtual void VUpdate(const Timer& timer) {}

	//This function should be overridden by the interface class.
	virtual ComponentId VGetComponentId()const = 0;

private:
	void SetOwner(StrongActorPtr pOwner) { mpOwner = pOwner; }
};

#endif // !ACTORCOMPONENT_H_
