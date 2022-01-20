#ifndef _MPEG4_ES_VIDEO_RTP_SOURCE_HH
#define _MPEG4_ES_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class MPEG4ESVideoRTPSource: public MultiFramedRTPSource {
public:
  static MPEG4ESVideoRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency);

protected:
  virtual ~MPEG4ESVideoRTPSource();

private:
  MPEG4ESVideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
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
