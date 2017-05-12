#include "ProcessManager.h"

unsigned int ProcessManager::UpdateProcessed(const Timer & timer)
{
	unsigned short int successCount = 0;
	unsigned short int failCount = 0;

	ProcessList::iterator it = mProcessList.begin();

	while (it != mProcessList.end())
	{
		//grab the next process
		StrongProcessPtr pCurrProcess = (*it);

		//save the iterator and increment old one in case we need to remove
		//this process from the list
		ProcessList::iterator thisIt = it;
		++it;

		//Process is uninitialized, so initialize it
		if (pCurrProcess->GetState() == Process::UNINITIALIZED)
			pCurrProcess->VOnInit();

		//give the process and update tick if it's running
		if (pCurrProcess->GetState() == Process::RUNNING)
			pCurrProcess->VOnUpdate(timer);

		//check to see if process is dead
		if (pCurrProcess->IsDead())
		{
			//run the appropriate exit function
			switch (pCurrProcess->GetState())
			{
			case Process::SUCCEEDED:
			{
				pCurrProcess->VOnSuccess();
				StrongProcessPtr pChild = pCurrProcess->RemoveChild();
				if (pChild)
					AttachProcess(pChild);
				else
					++successCount; //only counts if the whole chain completed
				break;
			}
			case Process::FAILED:
			{
				pCurrProcess->VOnFail();
				++failCount;
				break;
			}
			case Process::ABORTED:
			{
				pCurrProcess->VOnAbort();
				++failCount;
				break;
			}
			}
			mProcessList.erase(thisIt);
		}
	}
	return ((successCount << 16) | failCount);
}
