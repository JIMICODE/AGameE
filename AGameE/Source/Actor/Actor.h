/*
	Almost all object inheir from actor.
	Conclude some importance component:render, audio and some charactor:player and so on.

	We can use Xml to create a Actor.
*/

#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include"..\Common\Vectors.h"
#include"ActorFactory.h"

class Actor
{
	friend class ActorFactory;

	typedef std::map<ComponentId, StrongActorComponentPtr> ActorComponents;
protected:
	ActorId mId;		//unique id for the actor
	ActorType mType;
	Vec3 mPosition;
	ActorComponents mComponents;	//all components this cator has

protected:
	virtual bool Init(ActorId Id, ActorType Type, Vec3 Position = Vec3());

public:
	explicit Actor(ActorId id);
	~Actor();

	//Accessors
	const Vec3& GetPosition() const { return mPosition; }
	const ActorId GetId() const { return mId; }

	bool Init(TiXmlElement* pData);
	bool Destroy();
	void Update(const Timer& timer);
private:
	//This function is called by the ActorFactory. No one else should be
	//adding components.
	void AddComponent(StrongActorComponentPtr pComponent);
};

#endif // !ACTOR_H_
