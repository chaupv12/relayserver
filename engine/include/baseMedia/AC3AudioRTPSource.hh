#ifndef _AC3_AUDIO_RTP_SOURCE_HH
#define _AC3_AUDIO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class AC3AudioRTPSource : public MultiFramedRTPSource {
public:
	static AC3AudioRTPSource*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat,
			unsigned rtpTimestampFrequency);

protected:
	virtual ~AC3AudioRTPSource();

private:
	AC3AudioRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency);
	// called only by createNew()

private:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;
};

#endif
