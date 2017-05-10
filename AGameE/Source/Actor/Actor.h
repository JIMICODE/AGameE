/*
	Almost all object inheir from actor.
	Conclude some importance component:render, audio and some charactor:player and so on.*/

#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include"..\Common\Vectors.h"
#include"..\Common\Utility.h"

class Actor
{
	friend class ActorFactory;
protected:
	ActorId mId;
	ActorType mType;
	Vec3 mPosition;

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
	bool Update();
private:
	Actor();
};

#endif // !ACTOR_H_
