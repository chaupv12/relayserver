#ifndef _H263_PLUS_VIDEO_RTP_SOURCE_HH
#define _H263_PLUS_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

#define SPECIAL_HEADER_BUFFER_SIZE 1000

class H263plusVideoRTPSource: public MultiFramedRTPSource {
public:
  static H263plusVideoRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency = 90000);

  // A data structure that stores copies of the special header bytes
  // from the most recent frame's RTP packets:
  unsigned char fNumSpecialHeaders;
  unsigned fSpecialHeaderBytesLength;
  unsigned char fSpecialHeaderBytes[SPECIAL_HEADER_BUFFER_SIZE];
  unsigned fPacketSizes[256];

protected:
  virtual ~H263plusVideoRTPSource();

private:
  H263plusVideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
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
