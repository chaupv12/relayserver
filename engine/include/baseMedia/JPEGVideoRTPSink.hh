#ifndef _JPEG_VIDEO_RTP_SINK_HH
#define _JPEG_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

class JPEGVideoRTPSink: public VideoRTPSink {
public:
  static JPEGVideoRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs);

protected:
  JPEGVideoRTPSink(BaseEnv& env, Groupsock* RTPgs);
	// called only by createNew()

  virtual ~JPEGVideoRTPSink();

private: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);

  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual
  Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
					 unsigned numBytesInFrame) const;
  virtual unsigned specialHeaderSize() const;
};

#endif
