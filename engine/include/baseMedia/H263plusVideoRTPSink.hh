#ifndef _H263_PLUS_VIDEO_RTP_SINK_HH
#define _H263_PLUS_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

class H263plusVideoRTPSink: public VideoRTPSink {
public:
  static H263plusVideoRTPSink* createNew(BaseEnv& env, Groupsock* RTPgs,
					 unsigned char rtpPayloadFormat,
					 u_int32_t rtpTimestampFrequency = 90000);

protected:
  H263plusVideoRTPSink(BaseEnv& env, Groupsock* RTPgs,
		       unsigned char rtpPayloadFormat,
		       u_int32_t rtpTimestampFrequency);
	// called only by createNew()

  virtual ~H263plusVideoRTPSink();

private: // redefined virtual functions:
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
