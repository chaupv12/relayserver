#ifndef _BASE_UTIL_ENV0_HH
#define _BASE_UTIL_ENV0_HH

#ifndef _BASEUTILENV_VERSION_HH
#include "BaseUtilEnv_version.hh"
#endif

#ifndef _USAGE_ENVIRONMENT_HH
#include "BaseEnv.hh"
#endif

#ifndef _DELAY_QUEUE_HH
#include "DelayQueue.hh"
#endif

#define RESULT_MSG_BUFFER_MAX 1000

// An abstract base class, useful for subclassing
// (e.g., to redefine the implementation of "operator<<")
class BaseUtilEnv0 : public BaseEnv {
public:
	// redefined virtual functions:
	virtual MsgString getResultMsg() const;

	virtual void setResultMsg(MsgString msg);
	virtual void setResultMsg(MsgString msg1, MsgString msg2);
	virtual void setResultMsg(MsgString msg1, MsgString msg2, MsgString msg3);
	virtual void setResultErrMsg(MsgString msg, int err = 0);

	virtual void appendToResultMsg(MsgString msg);

	virtual void reportBackgroundError();

protected:
	BaseUtilEnv0(TaskScheduler& taskScheduler);
	virtual ~BaseUtilEnv0();

private:
	void reset();

	char fResultMsgBuffer[RESULT_MSG_BUFFER_MAX];
	unsigned fCurBufferSize;
	unsigned fBufferMaxSize;
};

class HandlerSet; // forward

#define MAX_NUM_EVENT_TRIGGERS 32

// An abstract base class, useful for subclassing
// (e.g., to redefine the implementation of socket event handling)
class BaseTaskScheduler0 : public TaskScheduler {
public:
	virtual ~BaseTaskScheduler0();

	virtual void SingleStep(unsigned maxDelayTime = 0) = 0;
	// "maxDelayTime" is in microseconds.  It allows a subclass to impose a limit
	// on how long "select()" can delay, in case it wants to also do polling.
	// 0 (the default value) means: There's no maximum; just look at the delay queue

public:
	// Redefined virtual functions:
	virtual TaskToken scheduleDelayedTask(int64_t microseconds, TaskFunc* proc, void* clientData);
	virtual void unscheduleDelayedTask(TaskToken& prevTask);

	virtual void doEventLoop(char volatile* watchVariable);

	virtual EventTriggerId createEventTrigger(TaskFunc* eventHandlerProc);
	virtual void deleteEventTrigger(EventTriggerId eventTriggerId);
	virtual void triggerEvent(EventTriggerId eventTriggerId, void* clientData = NULL);

protected:
	BaseTaskScheduler0();

protected:
	// To implement delayed operations:
	DelayQueue fDelayQueue;

	// To implement background reads:
	HandlerSet* fHandlers;
	int fLastHandledSocketNum;

	// To implement event triggers:
	EventTriggerId volatile fTriggersAwaitingHandling; // implemented as a 32-bit bitmap
	EventTriggerId fLastUsedTriggerMask; // implemented as a 32-bit bitmap
	TaskFunc* fTriggeredEventHandlers[MAX_NUM_EVENT_TRIGGERS];
	void* fTriggeredEventClientDatas[MAX_NUM_EVENT_TRIGGERS];
	unsigned fLastUsedTriggerNum; // in the range [0,MAX_NUM_EVENT_TRIGGERS)
};

#endif
