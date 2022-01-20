#ifndef _MP3_ADU_TRANSCODER_HH
#define _MP3_ADU_TRANSCODER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class MP3ADUTranscoder : public FramedFilter {
public:
	static MP3ADUTranscoder* createNew(BaseEnv& env, unsigned outBitrate /* in kbps */, FramedSource* inputSource);

	unsigned outBitrate() const { return fOutBitrate; }
protected:
	MP3ADUTranscoder(BaseEnv& env, unsigned outBitrate /* in kbps */, FramedSource* inputSource);
	// called only by createNew()
	virtual ~MP3ADUTranscoder();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();
	virtual void getAttributes() const;

private:
	static void afterGettingFrame(void* clientData, unsigned numBytesRead, unsigned numTruncatedBytes, struct timeval presentationTime, unsigned durationInMicroseconds);
	void afterGettingFrame1(unsigned numBytesRead, unsigned numTruncatedBytes, struct timeval presentationTime, unsigned durationInMicroseconds);

private:
	unsigned fOutBitrate; // in kbps
	unsigned fAvailableBytesForBackpointer;

	unsigned char* fOrigADU;
	// used to store incoming ADU prior to transcoding
};

#endif
