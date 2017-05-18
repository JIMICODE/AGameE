#pragma once
#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include"..\Common\Utility.h"
#include"EventData.h"

typedef std::function<void(IEventDataPtr)> EventListenerDelegate;

class IEventManager
{
public:
	enum eConstants {kINFINITE = 0xffffffff};

	explicit IEventManager(const char *pName, bool setAsGlobal);
	virtual ~IEventManager();

	//Registers a delegate function that will get call when the evnet
	//type is triggered. Return true if successful, false if not
	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;

	virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;

	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;

	virtual bool VTickUpdate(unsigned long maxMillis = kINFINITE) = 0;

	static IEventManager* Get(void);
};

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class EventManager : public IEventManager
{
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventDataPtr> EventQueue;

	EventListenerMap m_eventListeners;
	EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
	int m_activeQueue; //index of actively processing queue. Events
					   //queues to the opposing queue

public:
	explicit EventManager(const char *pName, bool setAsGlobal);
	virtual ~EventManager() {}

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;

	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;

	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const override;

	virtual bool VQueueEvent(const IEventDataPtr& pEvent) override;

	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) override;

	virtual bool VTickUpdate(unsigned long maxMillis = kINFINITE) override;
};

#endif // !EVENTMANAGER_H_
