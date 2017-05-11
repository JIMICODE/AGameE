#include"ActorFactory.h"

ActorFactory::ActorFactory()
{
	//TO DO
}

ActorFactory::~ActorFactory()
{
	//TO DO
}

StrongActorPtr ActorFactory::CreateActor(const char* actorResource)
{
	
	//Grab the root XML node
	TiXmlElement* pRoot;//no...........

	if (!pRoot)
	{
		//TO DO
	}

	StrongActorPtr pActor(new Actor(GetNextActorId()));

	if (!pActor->Init(pRoot))
	{
		return StrongActorPtr();
	}

	//Loop through each child element and load the component
	for (TiXmlElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		StrongActorComponentPtr pComponent(CreateComponent(pNode));
		if (pComponent)
		{
			pActor->AddComponent(pComponent);
			pComponent->SetOwner(pActor);
		}
		else 
		{
			return StrongActorPtr();
		}
	}
	/*
	*
	* TO DO
	*
	*/
	return StrongActorPtr();
}

StrongActorComponentPtr ActorFactory::CreateComponent(TiXmlElement * pData)
{
	std::string name(pData->Value());

	StrongActorComponentPtr pComponent;

	auto findIt = mActorComponentCreators.find(name);
	if (findIt != mActorComponentCreators.end())
	{
		ActorComponentCreator creator = findIt->second;
		pComponent.reset(creator());
	}
	else
	{
		//Error...
		//TO DO
		return StrongActorComponentPtr(); //fail
	}

	//initalize the component if we found one
	if (pComponent)
	{
		if (!pComponent->VInit(pData))
		{
			//Error
			//TO DO
			return StrongActorComponentPtr(); //fail
		}
	}
	//pComponent will be nullptr if the compoment wasn't found.
	return pComponent;
}
