/*All actor created by actor factory.*/
#pragma once
#ifndef ACTORFACTORY_H_
#define ACTORFACTORY_H_

#include"..\Common\TypeDef.h"
#include"ActorComponent.h"
#include"Actor.h"

class ActorFactory
{
	ActorId mLastActorId;
public:
	ActorFactory();
	~ActorFactory();

	StrongActorPtr CreateActor();

private:
	ActorId GetNextActorId() { ++mLastActorId; return mLastActorId; }
};

#endif // !ACTORFACTORY_H_
