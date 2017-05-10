#pragma once
#ifndef ACTORCOMPONENT_H_
#define ACTORCOMPONENT_H_
//#include"ActorFactory.h"

class ActorComponent
{
	friend class ActorFactory;

protected:
	StrongActorPtr mpOwner;

public:
	virtual ~ActorComponent() {}

	//These functions are meant to be overridden by the implementation
	//classed of the components.
	virtual bool VInit() = 0;
	virtual void VUpdate();

private:
	void SetOwner(StrongActorPtr pOwner) { mpOwner = pOwner; }
};

#endif // !ACTORCOMPONENT_H_
