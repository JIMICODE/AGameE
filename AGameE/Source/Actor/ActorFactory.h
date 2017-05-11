/*All actor created by actor factory.*/
#pragma once
#ifndef ACTORFACTORY_H_
#define ACTORFACTORY_H_

#include"..\Common\Utility.h"
#include"..\Common\TypeDef.h"
#include"ActorComponent.h"
#include"Actor.h"

typedef ActorComponent* (*ActorComponentCreator)(void);
typedef std::map<std::string, ActorComponentCreator> ActorComponentCreatorMap;

//some actor typedefs to make code more beautiful
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef unsigned long ComponentId;

class ActorFactory
{
	ActorId mLastActorId;
public:
	ActorFactory();
	~ActorFactory();
protected:
	ActorComponentCreatorMap mActorComponentCreators;
public:
	//Will have feature version
	StrongActorPtr CreateActor(const char* actorResource);

protected:
	virtual StrongActorComponentPtr CreateComponent(TiXmlElement* pData);

private:
	ActorId GetNextActorId() { ++mLastActorId; return mLastActorId; }
};

#endif // !ACTORFACTORY_H_
