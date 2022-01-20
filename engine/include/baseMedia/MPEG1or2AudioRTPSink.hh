#ifndef _MPEG_1OR2_AUDIO_RTP_SINK_HH
#define _MPEG_1OR2_AUDIO_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class MPEG1or2AudioRTPSink: public AudioRTPSink {
public:
  static MPEG1or2AudioRTPSink* createNew(BaseEnv& env,
				     Groupsock* RTPgs);

protected:
  MPEG1or2AudioRTPSink(BaseEnv& env, Groupsock* RTPgs);
	// called only by createNew()

  virtual ~MPEG1or2AudioRTPSink();

private: // redefined virtual functions:
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual unsigned specialHeaderSize() const;
};

#endif
