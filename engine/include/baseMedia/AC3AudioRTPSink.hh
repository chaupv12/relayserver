#ifndef _AC3_AUDIO_RTP_SINK_HH
#define _AC3_AUDIO_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class AC3AudioRTPSink : public AudioRTPSink {
public:
	static AC3AudioRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs, u_int8_t rtpPayloadFormat, u_int32_t rtpTimestampFrequency);

protected:
	// called only by createNew()
	AC3AudioRTPSink(BaseEnv& env, Groupsock* RTPgs, u_int8_t rtpPayloadFormat, u_int32_t rtpTimestampFrequency);
	virtual ~AC3AudioRTPSink();

private: // redefined virtual functions:
	virtual Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart, unsigned numBytesInFrame) const;
	virtual void doSpecialFrameHandling(unsigned fragmentationOffset, unsigned char* frameStart, unsigned numBytesInFrame, struct timeval framePresentationTime, unsigned numRemainingBytes);
	virtual unsigned specialHeaderSize() const;

private:
	// used only if a frame gets fragmented across multiple packets
	unsigned char fTotNumFragmentsUsed;
};

#endif
