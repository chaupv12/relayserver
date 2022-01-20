#ifndef _H261_VIDEO_RTP_SOURCE_HH
#define _H261_VIDEO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class H261VideoRTPSource: public MultiFramedRTPSource {
public:
  static H261VideoRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat = 31,
	    unsigned rtpTimestampFrequency = 90000);

  u_int32_t lastSpecialHeader() const {return fLastSpecialHeader;}

protected:
  virtual ~H261VideoRTPSource();

private:
  H261VideoRTPSource(BaseEnv& env, Groupsock* RTPgs,
			 unsigned char rtpPayloadFormat,
			 unsigned rtpTimestampFrequency);
      // called only by createNew()

private:
  // redefined virtual functions:
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  virtual char const* MIMEtype() const;

private:
  u_int32_t fLastSpecialHeader;
};

#endif
