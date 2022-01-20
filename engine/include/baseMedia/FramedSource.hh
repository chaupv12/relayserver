#ifndef _FRAMED_SOURCE_HH
#define _FRAMED_SOURCE_HH

#ifndef _NET_COMMON_H
#include "NetCommon.h"
#endif
#ifndef _MEDIA_SOURCE_HH
#include "MediaSource.hh"
#endif

class FramedSource : public MediaSource {
public:
	static Boolean lookupByName(BaseEnv& env, char const* sourceName, FramedSource*& resultSource);

	typedef void (afterGettingFunc)(void* clientData, unsigned frameSize, unsigned numTruncatedBytes, struct timeval presentationTime, unsigned durationInMicroseconds);
	typedef void (onCloseFunc)(void* clientData);
	void getNextFrame(unsigned char* to, unsigned maxSize, afterGettingFunc* afterGettingFunc, void* afterGettingClientData, onCloseFunc* onCloseFunc, void* onCloseClientData);

	static void handleClosure(void* clientData);
	void handleClosure();
	// This should be called (on ourself) if the source is discovered
	// to be closed (i.e., no longer readable)

	void stopGettingFrames();

	virtual unsigned maxFrameSize() const;
	// size of the largest possible frame that we may serve, or 0
	// if no such maximum is known (default)

	virtual void doGetNextFrame() = 0;
	// called by getNextFrame()

	Boolean isCurrentlyAwaitingData() const { return fIsCurrentlyAwaitingData; }

	static void afterGetting(FramedSource* source);
	// doGetNextFrame() should arrange for this to be called after the
	// frame has been read (*iff* it is read successfully)

protected:
	FramedSource(BaseEnv& env); // abstract base class
	virtual ~FramedSource();

	virtual void doStopGettingFrames();

protected:
	// The following variables are typically accessed/set by doGetNextFrame()
	unsigned char* fTo; // in
	unsigned fMaxSize; // in
	unsigned fFrameSize; // out
	unsigned fNumTruncatedBytes; // out
	struct timeval fPresentationTime; // out
	unsigned fDurationInMicroseconds; // out

private:
	// redefined virtual functions:
	virtual Boolean isFramedSource() const;

private:
	afterGettingFunc* fAfterGettingFunc;
	void* fAfterGettingClientData;
	onCloseFunc* fOnCloseFunc;
	void* fOnCloseClientData;

	Boolean fIsCurrentlyAwaitingData;
};

#endif
