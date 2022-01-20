#ifndef _MPEG_1OR2_VIDEO_RTP_SOURCE_HH
#define _MPEG_1OR2_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class MPEG1or2VideoRTPSource: public MultiFramedRTPSource {
public:
  static MPEG1or2VideoRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat = 32,
	    unsigned rtpPayloadFrequency = 90000);

protected:
  virtual ~MPEG1or2VideoRTPSource();

private:
  MPEG1or2VideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
		     unsigned char rtpPayloadFormat,
		     unsigned rtpTimestampFrequency);
      // called only by createNew()

private:
  // redefined virtual functions:
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  virtual Boolean packetIsUsableInJitterCalculation(unsigned char* packet,
						    unsigned packetSize);
  virtual char const* MIMEtype() const;
};

#endif
