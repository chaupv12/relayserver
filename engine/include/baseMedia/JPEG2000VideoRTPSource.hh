#ifndef _JPEG2000_VIDEO_RTP_SOURCE_HH
#define _JPEG2000_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class JPEG2000VideoRTPSource: public MultiFramedRTPSource {
public:
  static JPEG2000VideoRTPSource* createNew(BaseEnv& env, Groupsock* RTPgs,
					   unsigned char rtpPayloadFormat,
					   unsigned rtpTimestampFrequency,
					   char const* sampling);

protected:
  virtual ~JPEG2000VideoRTPSource();

protected:
  JPEG2000VideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
			 unsigned char rtpPayloadFormat,
			 unsigned rtpTimestampFrequency,
			 char const* sampling);
    // called only by createNew()

private:
  // redefined virtual functions:
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  virtual char const* MIMEtype() const;

private:
  char* fSampling;
};

#endif
