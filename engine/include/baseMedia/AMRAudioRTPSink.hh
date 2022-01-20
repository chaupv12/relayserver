#ifndef _AMR_AUDIO_RTP_SINK_HH
#define _AMR_AUDIO_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class AMRAudioRTPSink: public AudioRTPSink {
public:
  static AMRAudioRTPSink* createNew(BaseEnv& env,
				    Groupsock* RTPgs,
				    unsigned char rtpPayloadFormat,
				    Boolean sourceIsWideband = False,
				    unsigned numChannelsInSource = 1);

  Boolean sourceIsWideband() const { return fSourceIsWideband; }

protected:
  AMRAudioRTPSink(BaseEnv& env, Groupsock* RTPgs,
		  unsigned char rtpPayloadFormat,
		  Boolean sourceIsWideband, unsigned numChannelsInSource);
	// called only by createNew()

  virtual ~AMRAudioRTPSink();

private: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual Boolean
  frameCanAppearAfterPacketStart(unsigned char const* frameStart,
				 unsigned numBytesInFrame) const;

  virtual unsigned specialHeaderSize() const;
  virtual char const* auxSDPLine();

private:
  Boolean fSourceIsWideband;
  char* fFmtpSDPLine;
};

#endif
