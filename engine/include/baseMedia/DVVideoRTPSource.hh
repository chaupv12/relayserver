#ifndef _DV_VIDEO_RTP_SOURCE_HH
#define _DV_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class DVVideoRTPSource: public MultiFramedRTPSource {
public:
  static DVVideoRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency);

protected:
  virtual ~DVVideoRTPSource();

private:
  DVVideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
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
