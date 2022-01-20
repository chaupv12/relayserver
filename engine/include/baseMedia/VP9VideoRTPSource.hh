#ifndef _VP9_VIDEO_RTP_SOURCE_HH
#define _VP9_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class VP9VideoRTPSource : public MultiFramedRTPSource {
public:
	static VP9VideoRTPSource*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat,
			unsigned rtpTimestampFrequency = 90000);

protected:
	VP9VideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency);
	// called only by createNew()

	virtual ~VP9VideoRTPSource();

protected:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;
};

#endif
