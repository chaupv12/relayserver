#ifndef _SIMPLE_RTP_SINK_HH
#define _SIMPLE_RTP_SINK_HH

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#include "MultiFramedRTPSink.hh"
#endif

class SimpleRTPSink : public MultiFramedRTPSink {
public:
	static SimpleRTPSink*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat,
			unsigned rtpTimestampFrequency,
			char const* sdpMediaTypeString,
			char const* rtpPayloadFormatName,
			unsigned numChannels = 1,
			Boolean allowMultipleFramesPerPacket = True,
			Boolean doNormalMBitRule = True);
	// "doNormalMBitRule" means: If the medium (i.e., "sdpMediaTypeString") is other than "audio", set the RTP "M" bit
	// on each outgoing packet iff it contains the last (or only) fragment of a frame.
	// Otherwise (i.e., if "doNormalMBitRule" is False, or the medium is "audio"), leave the "M" bit unset.

	void setMBitOnNextPacket() { fSetMBitOnNextPacket = True; } // hack for optionally setting the RTP 'M' bit from outside the class

protected:
	SimpleRTPSink(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency,
		char const* sdpMediaTypeString,
		char const* rtpPayloadFormatName,
		unsigned numChannels,
		Boolean allowMultipleFramesPerPacket,
		Boolean doNormalMBitRule);
	// called only by createNew()

	virtual ~SimpleRTPSink();

protected: // redefined virtual functions
	virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
		unsigned char* frameStart,
		unsigned numBytesInFrame,
		struct timeval framePresentationTime,
		unsigned numRemainingBytes);
	virtual
		Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
			unsigned numBytesInFrame) const;
	virtual char const* sdpMediaType() const;

private:
	char const* fSDPMediaTypeString;
	Boolean fAllowMultipleFramesPerPacket;
	Boolean fSetMBitOnLastFrames, fSetMBitOnNextPacket;
};

#endif
