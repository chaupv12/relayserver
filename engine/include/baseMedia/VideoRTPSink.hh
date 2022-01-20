#ifndef _VIDEO_RTP_SINK_HH
#define _VIDEO_RTP_SINK_HH

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#include "MultiFramedRTPSink.hh"
#endif

class VideoRTPSink : public MultiFramedRTPSink {
protected:
	VideoRTPSink(BaseEnv& env,
		Groupsock* rtpgs, unsigned char rtpPayloadType,
		unsigned rtpTimestampFrequency,
		char const* rtpPayloadFormatName);
	// (we're an abstract base class)
	virtual ~VideoRTPSink();

private: // redefined virtual functions:
	virtual char const* sdpMediaType() const;
};

#endif
