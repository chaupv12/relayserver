#ifndef _MP3_ADU_RTP_SINK_HH
#define _MP3_ADU_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class MP3ADURTPSink: public AudioRTPSink {
public:
  static MP3ADURTPSink* createNew(BaseEnv& env, Groupsock* RTPgs,
				  unsigned char RTPPayloadType);

protected:
  virtual ~MP3ADURTPSink();

private:
  MP3ADURTPSink(BaseEnv& env, Groupsock* RTPgs,
		unsigned char RTPPayloadType);
	// called only by createNew()


private:
  // Redefined virtual functions:
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual unsigned specialHeaderSize() const;

private:
  unsigned fCurADUSize; // used when fragmenting over multiple RTP packets
};

#endif
