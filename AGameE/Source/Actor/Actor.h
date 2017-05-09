/*
	Almost all object inheir from actor.
	Conclude some importance component:render, audio and some charactor:player and so on.*/

#pragma once
#ifndef ACTOR_H_
#define ACTOR_H_

#include"..\Common\Vectors.h"
#include"ActorFactory.h"

typedef int ActorId;

enum ActorType {
	RenderComponent,
	AudioComponent,
	Player,
	Enemy
};

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
	const Vec3& GetPosition() const { return mPosition; }
	const ActorId GetID() const { return mId; }

	virtual ~Actor();

private:
	Actor();
};

#endif // !ACTOR_H_
