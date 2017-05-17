#pragma once
#ifndef DESTROY_ACTOR_H_
#define DESTROY_ACTOR_H_

#include"EventData.h"

class EvtData_Destroy_Actor : public BaseEventData
{
	ActorId m_id;

public:
	static const EventType sk_EventType;

	explicit EvtData_Destroy_Actor(ActorId id) : m_id(id) {}

	explicit EvtData_Destroy_Actor(std::istrstream& in)
	{
		in >> m_id;
	}

	virtual const EventType& VGetEventType() const override
	{
		return sk_EventType;
	}

	virtual IEventDataPtr VCopy()const override
	{
		return IEventDataPtr(new EvtData_Destroy_Actor(m_id));
	}

	virtual void VSerialize(std::ostrstream &out)const override
	{
		out << m_id;
	}

	virtual const char* GetName()const override
	{
		return "EvtData_Destroy_Actor";
	}

	ActorId GetId()const { return m_id; }
};

#endif // !DESTROY_ACTOR_H_
