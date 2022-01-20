#ifndef _THEORA_VIDEO_RTP_SOURCE_HH
#define _THEORA_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class TheoraVideoRTPSource : public MultiFramedRTPSource {
public:
	static TheoraVideoRTPSource*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat);

	u_int32_t curPacketIdent() const { return fCurPacketIdent; } // The current "Ident" field; only the low-order 24 bits are used

protected:
	TheoraVideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat);
	// called only by createNew()

	virtual ~TheoraVideoRTPSource();

protected:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;

private:
	u_int32_t fCurPacketIdent; // only the low-order 24 bits are used
};

#endif
