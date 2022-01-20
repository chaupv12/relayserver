#ifndef _GSM_AUDIO_RTP_SINK_HH
#define _GSM_AUDIO_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class GSMAudioRTPSink: public AudioRTPSink {
public:
  static GSMAudioRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs);

protected:
  GSMAudioRTPSink(BaseEnv& env, Groupsock* RTPgs);
	// called only by createNew()

  virtual ~GSMAudioRTPSink();

private: // redefined virtual functions:
  virtual
  Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
					 unsigned numBytesInFrame) const;
};

#endif
