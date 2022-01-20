#ifndef _TEXT_RTP_SINK_HH
#define _TEXT_RTP_SINK_HH

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#include "MultiFramedRTPSink.hh"
#endif

class TextRTPSink : public MultiFramedRTPSink {
protected:
	TextRTPSink(BaseEnv& env,
		Groupsock* rtpgs, unsigned char rtpPayloadType,
		unsigned rtpTimestampFrequency,
		char const* rtpPayloadFormatName);
	// (we're an abstract base class)
	virtual ~TextRTPSink();

private: // redefined virtual functions:
	virtual char const* sdpMediaType() const;
};

#endif
