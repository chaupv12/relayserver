#ifndef _BASE_UTIL_ENV_HH
#define _BASE_UTIL_ENV_HH

#ifndef _BASE_UTIL_ENV0_HH
#include "BaseUtilEnv0.hh"
#endif

class BaseUtilEnv : public BaseUtilEnv0 {
public:
	static BaseUtilEnv* createNew(TaskScheduler& taskScheduler);

	// redefined virtual functions:
	virtual int getErrno() const;

	virtual BaseEnv& operator<<(char const* str);
	virtual BaseEnv& operator<<(int i);
	virtual BaseEnv& operator<<(unsigned u);
	virtual BaseEnv& operator<<(double d);
	virtual BaseEnv& operator<<(void* p);

protected:
	BaseUtilEnv(TaskScheduler& taskScheduler);
	// called only by "createNew()" (or subclass constructors)
	virtual ~BaseUtilEnv();
};


class BaseTaskScheduler : public BaseTaskScheduler0 {
public:
	static BaseTaskScheduler* createNew(unsigned maxSchedulerGranularity = 10000/*microseconds*/);
	// "maxSchedulerGranularity" (default value: 10 ms) specifies the maximum time that we wait (in "select()") before
	// returning to the event loop to handle non-socket or non-timer-based events, such as 'triggered events'.
	// You can change this is you wish (but only if you know what you're doing!), or set it to 0, to specify no such maximum time.
	// (You should set it to 0 only if you know that you will not be using 'event triggers'.)
	virtual ~BaseTaskScheduler();

protected:
	BaseTaskScheduler(unsigned maxSchedulerGranularity);
	// called only by "createNew()"

	static void schedulerTickTask(void* clientData);
	void schedulerTickTask();

protected:
	// Redefined virtual functions:
	virtual void SingleStep(unsigned maxDelayTime);

	virtual void setBackgroundHandling(int socketNum, int conditionSet, BackgroundHandlerProc* handlerProc, void* clientData);
	virtual void moveSocketHandling(int oldSocketNum, int newSocketNum);

protected:
	unsigned fMaxSchedulerGranularity;

	// To implement background operations:
	int fMaxNumSockets;
	fd_set fReadSet;
	fd_set fWriteSet;
	fd_set fExceptionSet;

private:
#if defined(__WIN32__) || defined(_WIN32)
	// Hack to work around a bug in Windows' "select()" implementation:
	int fDummySocketNum;
#endif
};

#endif
