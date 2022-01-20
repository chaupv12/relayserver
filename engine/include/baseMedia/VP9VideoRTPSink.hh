#ifndef _VP9_VIDEO_RTP_SINK_HH
#define _VP9_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

class VP9VideoRTPSink : public VideoRTPSink {
public:
	static VP9VideoRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat);

protected:
	VP9VideoRTPSink(BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat);
	// called only by createNew()

	virtual ~VP9VideoRTPSink();

private: // redefined virtual functions:
	virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
		unsigned char* frameStart,
		unsigned numBytesInFrame,
		struct timeval framePresentationTime,
		unsigned numRemainingBytes);
	virtual
		Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
			unsigned numBytesInFrame) const;
	virtual unsigned specialHeaderSize() const;
};

#endif
