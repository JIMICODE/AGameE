#include "EventManager.h"

EventManager::EventManager(const char * pName, bool setAsGlobal) : IEventManager(pName, setAsGlobal)
{
	m_activeQueue = 0;
}

bool EventManager::VAddListener(const EventListenerDelegate & eventDelegate, const EventType & type)
{
	//this will find or creates the entry
	EventListenerList& eventListenerList = m_eventListeners[type];

	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		//if (eventDelegate == (*it))
		//{
			//will fixed
		//}
	}
	eventListenerList.push_back(eventDelegate);
	return true;
}

bool EventManager::VRemoveListener(const EventListenerDelegate & eventDelegate, const EventType & type)
{
	bool success = false;

	auto findIt = m_eventListeners.find(type);
	if (findIt != m_eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;

		for (auto it = listeners.begin();it != listeners.end(); ++it)
		{	/*
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				//Wo don't need to continue because it should be impossible for
				//jthe same delegate function to be registered for the same event
				//more than once
				break;
			}*/
		}
	}
	return success;
}

bool EventManager::VTriggerEvent(const IEventDataPtr & pEvent) const
{
	bool processed = false;

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			listener(pEvent);
			processed = true;
		}
	}
	return processed;
}

bool EventManager::VQueueEvent(const IEventDataPtr & pEvent)
{
	assert(m_activeQueue >= 0);
	assert(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());

	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		return true;
	}
	else
	{
		return false;
	}
}

bool EventManager::VAbortEvent(const EventType & type, bool allOfType)
{
	assert(m_activeQueue >= 0);
	assert(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	bool success = false;
	auto findIt = m_eventListeners.find(type);

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();

		while (it != eventQueue.end())
		{
			//Removing an item from the queue will invalidate the iterator, so 
			//have it point to the next member. All work inside this loop will
			//be done using thisIt.
			auto thisIt = it;
			++it;
			if ((*thisIt)->VGetEventType == type)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}
	return success;
}

bool EventManager::VTickUpdate(unsigned long maxMillis)
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis));

	//swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	//Provess the queue
	while (!m_queues[queueToProcess].empty())
	{
		//pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();

		const EventType& eventType = pEvent->VGetEventType();

		//find all the delegate functions refistered for this event
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			//call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				listener(pEvent);
			}
		}

		//check to see if time ran out
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			//Log
			break;
		}
	}
	//If we couldn't process all of the events, push the remaining events to 
	//the new active queue.
	//To preserve sequencing , go back_to_front, inserting them at the head of the active queue.
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_back(pEvent);
		}
	}
	return queueFlushed;
}

IEventManager * IEventManager::Get(void)
{
}
