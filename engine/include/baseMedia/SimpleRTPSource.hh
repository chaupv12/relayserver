#ifndef _SIMPLE_RTP_SOURCE_HH
#define _SIMPLE_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class SimpleRTPSource : public MultiFramedRTPSource {
public:
	static SimpleRTPSource* createNew(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency,
		char const* mimeTypeString,
		unsigned offset = 0,
		Boolean doNormalMBitRule = True);
	// "doNormalMBitRule" means: If the medium is not audio, use the RTP "M"
	// bit on each incoming packet to indicate the last (or only) fragment
	// of a frame.  Otherwise (i.e., if "doNormalMBitRule" is False, or the medium is "audio"), the "M" bit is ignored.

protected:
	SimpleRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency,
		char const* mimeTypeString, unsigned offset,
		Boolean doNormalMBitRule);
	// called only by createNew(), or by subclass constructors
	virtual ~SimpleRTPSource();

protected:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;

private:
	char const* fMIMEtypeString;
	unsigned fOffset;
	Boolean fUseMBitForFrameEnd;
};

#endif
