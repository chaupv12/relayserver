#ifndef _JPEG2000_VIDEO_RTP_SINK_HH
#define _JPEG2000_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

class JPEG2000VideoRTPSink: public VideoRTPSink {
public:
  static JPEG2000VideoRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs);

protected:
  JPEG2000VideoRTPSink(BaseEnv& env, Groupsock* RTPgs);
	// called only by createNew()

  virtual ~JPEG2000VideoRTPSink();

private: // redefined virtual functions:
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual unsigned specialHeaderSize() const;
};

#endif
