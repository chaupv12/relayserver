#ifndef _MP3_ADU_SOURCE_HH
#define _MP3_ADU_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class MP3ADURTPSource: public MultiFramedRTPSource {
public:
  static MP3ADURTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency = 90000);

protected:
  virtual ~MP3ADURTPSource();

private:
  MP3ADURTPSource(BaseEnv& env, Groupsock* RTPgs,
		  unsigned char rtpPayloadFormat,
		  unsigned rtpTimestampFrequency);
      // called only by createNew()

private:
  // redefined virtual functions:
  virtual char const* MIMEtype() const;
};

#endif
