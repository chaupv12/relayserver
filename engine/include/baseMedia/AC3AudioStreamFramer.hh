#ifndef _AC3_AUDIO_STREAM_FRAMER_HH
#define _AC3_AUDIO_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class AC3AudioStreamFramer : public FramedFilter {
public:
	static AC3AudioStreamFramer*
		createNew(BaseEnv& env, FramedSource* inputSource,
			unsigned char streamCode = 0);
	// If "streamCode" != 0, then we assume that there's a 1-byte code at the beginning of each chunk of data that we read from
	// our source.  If that code is not the value we want, we discard the chunk of data.
	// However, if "streamCode" == 0 (the default), then we don't expect this 1-byte code.

	unsigned samplingRate();

	void flushInput(); // called if there is a discontinuity (seeking) in the input

private:
	AC3AudioStreamFramer(BaseEnv& env, FramedSource* inputSource,
		unsigned char streamCode);
	// called only by createNew()
	virtual ~AC3AudioStreamFramer();

	static void handleNewData(void* clientData,
		unsigned char* ptr, unsigned size,
		struct timeval presentationTime);
	void handleNewData(unsigned char* ptr, unsigned size);

	void parseNextFrame();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();

private:
	struct timeval currentFramePlayTime() const;

private:
	struct timeval fNextFramePresentationTime;

private: // parsing state
	class AC3AudioStreamParser* fParser;
	unsigned char fOurStreamCode;
	friend class AC3AudioStreamParser; // hack
};

#endif
