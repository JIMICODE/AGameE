#pragma once
#ifndef DESTROY_ACTOR_H_
#define DESTROY_ACTOR_H_

#include"EventData.h"

// {183EC7C5-EF54-4D99-957B-7FFC6007966C}
DEFINE_GUID(Destory_Actor ,
	0x183ec7c5, 0xef54, 0x4d99, 0x95, 0x7b, 0x7f, 0xfc, 0x60, 0x7, 0x96, 0x6c);


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
