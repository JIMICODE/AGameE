#pragma once
#ifndef TIMER_H_
#define TIMER_H_

#include<Windows.h>

class Timer
{
public:
	Timer();

	float TotalTime()const;	//in seconds
	float DeltaTime()const;	//in seconds

	void Reset();	//call before message loop.
	void Start();	//call when unpaused
	void Stop();	//call when paused
	void Tick();	//call every frame

protected:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;

};

#endif // !TIMER_H_
