#include "Timer.h"

Timer::Timer():
	mSecondsPerCount(0.0),
	mDeltaTime(-1.0),
	mBaseTime(0),
	mPausedTime(0),
	mPrevTime(0),
	mCurrTime(0),
	mStopped(false)
{
	__int64 countPerSec;

	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
	mSecondsPerCount = 1.0 / (double)countPerSec;
}

float Timer::TotalTime() const
{
	//If we stopped, do not count the time that has passed
	//since we stopped. Moreover, if we previously already had
	//a pause, the distance mStopTime - mBaseTime includes paused
	//time, which do not want to count. To correct this, we can
	//subtract the paused time from mStopTime:
	//
	//		previous paused time
	//		|<---------->|
	//---*--------*-----------------*-------------*------------*--------->time
	//mBaseTime					mStopTime		mCurrTime

	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}

	//The distance mCurrTIme - mBaseTime includes paused time, 
	//whick wo de not want to count. TO correct this, we can subtract
	//the paused time from mCurrTime:
	//
	//(mCurrTime - mPausedTime) - mBaseTIme
	//
	//			|-----paused time---->|
	//-----*------------*-----------------*-----------*------->time
	//mBaseTime		mStopTime			startTime	mCurrTime

	else
	{
		return(float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
}

float Timer::DeltaTime() const
{
	return (float)mDeltaTime;
}

void Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void Timer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//Accumulate the time elapsed between stop and start pairs.
	//
	//		|<--------------d-------------->|
	//------*--------------------------------*------------>time
	//	mStopTime							startTime

	//If we are resuming the timer from a stopped state...
	if (mStopped)
	{
		//then accumulate the paused time.
		mPausedTime += (startTime - mStopTime);

		//since we are starting the timer back up, the current
		//previous time is not vaild, as it occurred while paused.
		//So reset it to the current time.
		mPrevTime = startTime;

		//no longer stopped...
		mStopTime = 0;
		mStopped = false;
	}
}

void Timer::Stop()
{
	//If wo are already stopped, then don't do anything
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//Onterwise, save the time we stopped at, and set
		//the Boolean flag indicating the timer is stopped.
		mStopTime = currTime;
		mStopped = true;
	}
}

void Timer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	//Get the time this frame.
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//Time difference between this frame and previous.
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	//Prepare for next frame
	mPrevTime = mCurrTime;

	//Forece nonegative.
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}
