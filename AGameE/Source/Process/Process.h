#pragma once
#ifndef PROCESS_H_
#define PROCESS_H_

#include"..\Common\Utility.h"
//some smart pointer typedef's
class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;

class Process
{
	friend class ProcessManager;

public:
	enum State
	{
		//Processes that are neither dead nor alive
		UNINITIALIZED = 0,	//created but not running
		REMOVED,	//removed from the process list but not destroyed; this
					//can happed when a process that is already running is parented
					//to another process.

		//Living processes
		RUNNING, //intialized and running
		PAUSED,	//initialized but paused

		//Dead Processes
		SUCCEEDED,	//completed successfully
		FAILED,		//failed to complete
		ABORTED		//aborted; may not have started
	};
private:
	State mState;				//the current state of the process
	StrongProcessPtr mpChild;	//the child process, if any
	
public:
	//construction
	Process();
	virtual ~Process();

protected:
	//interface; these functions should be overridden by the subclass as needed
	virtual void VOnInit() { mState = RUNNING; }
	virtual void VOnUpdate(const Timer& timer) = 0;
	virtual void VOnSuccess() {}
	virtual void VOnFail() {}
	virtual void VOnAbort() {}

public:
	//Functions for ending the process
	inline void Succeed();
	inline void Fail();

	//pause
	inline void Pause();
	inline void UnPause();

	//accessors
	State GetState()const { return mState; }
	bool IsAlive()const { return (mState == RUNNING || mState == PAUSED); }
	bool IsDead()const
	{
		return (mState == SUCCEEDED || mState == FAILED || mState == ABORTED);
	}
	bool IsRemoved()const { return mState == REMOVED; }
	bool IsPaused() { return mState == PAUSED; }

	//child functions
	inline void AttachChild(StrongProcessPtr pChild);
	StrongProcessPtr RemoveChild();	//releases ownership of the child
	StrongProcessPtr PeekChild() { return mpChild; }//doesn't release ownershp of child

private:
	void SetState(State newState) { mState = newState; }
};

#endif // ! PROCESS_H_
