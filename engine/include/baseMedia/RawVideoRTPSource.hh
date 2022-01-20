#ifndef _RAW_VIDEO_RTP_SOURCE_HH
#define _RAW_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class RawVideoRTPSource : public MultiFramedRTPSource {
public:
	static RawVideoRTPSource* createNew(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency);

	u_int16_t currentLineNumber() const; // of the most recently-read/processed scan line
	u_int8_t currentLineFieldId() const; // of the most recently-read/processed scan line (0 or 1)
	u_int16_t currentOffsetWithinLine() const; // of the most recently-read/processed scan line

protected:
	RawVideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency = 90000);
	// called only by createNew()

	virtual ~RawVideoRTPSource();

protected:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;

private:
	unsigned fNumLines; // in the most recently read packet
	unsigned fNextLine; // index of the next AU Header to read
	struct LineHeader* fLineHeaders;

	friend class RawVideoBufferedPacket;
};

#endif
