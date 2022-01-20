#ifndef _DV_VIDEO_RTP_SINK_HH
#define _DV_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif
#ifndef _DV_VIDEO_STREAM_FRAMER_HH
#include "DVVideoStreamFramer.hh"
#endif

class DVVideoRTPSink: public VideoRTPSink {
public:
  static DVVideoRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat);
  char const* auxSDPLineFromFramer(DVVideoStreamFramer* framerSource);

protected:
  DVVideoRTPSink(BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat);
	// called only by createNew()

  virtual ~DVVideoRTPSink();

private: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual unsigned computeOverflowForNewFrame(unsigned newFrameSize) const;
  virtual char const* auxSDPLine();

private:
  char* fFmtpSDPLine;
};

#endif
