#pragma once

#ifndef EVENTDATA_H_
#define EVENTDATA_H_

#include"..\Common\Utility.h"
typedef unsigned long EventType;

class IEventData;

typedef std::shared_ptr<IEventData> IEventDataPtr;

class IEventData
{
public:
	virtual const EventType& VGetEventType()const = 0;
	virtual float VGetTimeStamp()const = 0;
	virtual void VSerialize(std::ostrstream& out)const = 0;
	virtual IEventDataPtr VCopy()const = 0;
	virtual const char* GetName()const = 0;
};

class BaseEventData : public IEventData
{
	const float mTimeStamp;

public:
	explicit BaseEventData(const float timeStamp = 0.0f);
	virtual ~BaseEventData() {}

	//Return the type of the event
	virtual const EventType& VGetEventType() const = 0;
	float VGetTimeStamp() const { return mTimeStamp; }

	//Serializing for network out
	virtual void VSerialize(std::ostrstream &out)const  override{}
};

#endif // ! EVENTDATA_H_
