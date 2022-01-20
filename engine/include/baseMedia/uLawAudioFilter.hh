#ifndef _ULAW_AUDIO_FILTER_HH
#define _ULAW_AUDIO_FILTER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

//16-bit PCM (in various byte orderings) -> 8-bit u-Law 

class uLawFromPCMAudioSource : public FramedFilter {
public:
	static uLawFromPCMAudioSource*
		createNew(BaseEnv& env, FramedSource* inputSource,
			int byteOrdering = 0);
	// "byteOrdering" == 0 => host order (the default)
	// "byteOrdering" == 1 => little-endian order
	// "byteOrdering" == 2 => network (i.e., big-endian) order

protected:
	uLawFromPCMAudioSource(BaseEnv& env, FramedSource* inputSource,
		int byteOrdering);
	// called only by createNew()
	virtual ~uLawFromPCMAudioSource();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);

private:
	int fByteOrdering;
	unsigned char* fInputBuffer;
	unsigned fInputBufferSize;
};


//u-Law -> 16-bit PCM (in host order) 

class PCMFromuLawAudioSource : public FramedFilter {
public:
	static PCMFromuLawAudioSource*
		createNew(BaseEnv& env, FramedSource* inputSource);

protected:
	PCMFromuLawAudioSource(BaseEnv& env,
		FramedSource* inputSource);
	// called only by createNew()
	virtual ~PCMFromuLawAudioSource();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);

private:
	unsigned char* fInputBuffer;
	unsigned fInputBufferSize;
};


//16-bit values (in host order) -> 16-bit network order

class NetworkFromHostOrder16 : public FramedFilter {
public:
	static NetworkFromHostOrder16*
		createNew(BaseEnv& env, FramedSource* inputSource);

protected:
	NetworkFromHostOrder16(BaseEnv& env, FramedSource* inputSource);
	// called only by createNew()
	virtual ~NetworkFromHostOrder16();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
};


//16-bit values (in network order) -> 16-bit host order

class HostFromNetworkOrder16 : public FramedFilter {
public:
	static HostFromNetworkOrder16*
		createNew(BaseEnv& env, FramedSource* inputSource);

protected:
	HostFromNetworkOrder16(BaseEnv& env, FramedSource* inputSource);
	// called only by createNew()
	virtual ~HostFromNetworkOrder16();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
};


//16-bit values: little-endian <-> big-endian

class EndianSwap16 : public FramedFilter {
public:
	static EndianSwap16* createNew(BaseEnv& env, FramedSource* inputSource);

protected:
	EndianSwap16(BaseEnv& env, FramedSource* inputSource);
	// called only by createNew()
	virtual ~EndianSwap16();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
};


//24-bit values: little-endian <-> big-endian

class EndianSwap24 : public FramedFilter {
public:
	static EndianSwap24* createNew(BaseEnv& env, FramedSource* inputSource);

protected:
	EndianSwap24(BaseEnv& env, FramedSource* inputSource);
	// called only by createNew()
	virtual ~EndianSwap24();

private:
	// Redefined virtual functions:
	virtual void doGetNextFrame();

private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
};

#endif
