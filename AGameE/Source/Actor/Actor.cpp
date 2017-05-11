#include "Actor.h"

bool Actor::Init(ActorId Id, ActorType Type, Vec3 Position)
{
	mId = Id;
	mType = Type;
	mPosition = Position;

	return true;
}

bool Actor::Init(TiXmlElement * pData)
{
	//TO DO
	return false;
}

bool Actor::Destroy()
{
	return false;
}

void Actor::Update(const Timer & timer)
{
}
