#ifndef _RAW_VIDEO_RTP_SINK_HH
#define _RAW_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

#ifndef _RAW_VIDEO_FRAME_PARAMETERS_HH
#include "RawVideoFrameParameters.hh"
#endif

class RawVideoRTPSink : public VideoRTPSink {
public:
	static RawVideoRTPSink*
		createNew(BaseEnv& env, Groupsock* RTPgs, u_int8_t rtpPayloadFormat,
			unsigned width, unsigned height, unsigned depth, // as defined by RFC 4175, sec 6.1
			char const* sampling, char const* colorimetry);

protected:
	RawVideoRTPSink(BaseEnv& env, Groupsock* RTPgs,
		u_int8_t rtpPayloadFormat,
		unsigned width, unsigned height, unsigned depth,
		char const* sampling, char const* colorimetry);
	// called only by createNew()

	virtual ~RawVideoRTPSink();

private: // redefined virtual functions:
	virtual char const* auxSDPLine(); // for the "a=fmtp:" SDP line

	virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
		unsigned char* frameStart,
		unsigned numBytesInFrame,
		struct timeval framePresentationTime,
		unsigned numRemainingBytes);
	virtual Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
		unsigned numBytesInFrame) const;
	virtual unsigned specialHeaderSize() const;
	virtual unsigned computeOverflowForNewFrame(unsigned newFrameSize) const;

private:
	char* fFmtpSDPLine;
	unsigned fLineIndex;
	RawVideoFrameParameters fP;

	unsigned getNumLinesInPacket(unsigned fragOffset, u_int16_t*& lengths, u_int16_t*& offsets) const;
	//  return the number of lines, their lengths and offsets from the fragmentation offset of the whole frame.
	// call delete[] on lengths and offsets after use of the function
};

#endif
