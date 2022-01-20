#ifndef _AUDIO_RTP_SINK_HH
#define _AUDIO_RTP_SINK_HH

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#include "MultiFramedRTPSink.hh"
#endif

class AudioRTPSink: public MultiFramedRTPSink {
protected:
  AudioRTPSink(BaseEnv& env,
	       Groupsock* rtpgs, unsigned char rtpPayloadType,
	       unsigned rtpTimestampFrequency,
	       char const* rtpPayloadFormatName,
	       unsigned numChannels = 1);
  // (we're an abstract base class)
  virtual ~AudioRTPSink();

private: // redefined virtual functions:
  virtual char const* sdpMediaType() const;
};

#endif
