#pragma once
#ifndef PROCESSMANAGER_H_
#define PROCESSMANAGET_H_

#include"Process.h"

class ProcessManager
{
	typedef std::list<StrongProcessPtr> ProcessList;
	ProcessList mProcessList;

public:
	//construction
	~ProcessManager();

	//interface
	unsigned int UpdateProcessed(const Timer& timer);
	WeakProcessPtr AttachProcess(StrongProcessPtr pProcess);
	void AbortAllProcessed(bool immediate);

	//accessors
	unsigned int GetProcessCount()const { return mProcessList.size(); }

private:
	void ClearAllProcessed();//should only be called by the destructor
};

#endif // !PROCESSMANAGER_H_
