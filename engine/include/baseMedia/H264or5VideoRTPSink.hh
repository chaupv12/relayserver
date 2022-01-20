#ifndef _H264_OR_5_VIDEO_RTP_SINK_HH
#define _H264_OR_5_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif
#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class H264or5VideoRTPSink: public VideoRTPSink {
protected:
  H264or5VideoRTPSink(int hNumber, // 264 or 265
		      BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat,
		      u_int8_t const* vps = NULL, unsigned vpsSize = 0,
		      u_int8_t const* sps = NULL, unsigned spsSize = 0,
		      u_int8_t const* pps = NULL, unsigned ppsSize = 0);
	// we're an abstrace base class
  virtual ~H264or5VideoRTPSink();

private: // redefined virtual functions:
  virtual Boolean continuePlaying();
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
						 unsigned numBytesInFrame) const;

protected:
  int fHNumber;
  FramedFilter* fOurFragmenter;
  char* fFmtpSDPLine;
  u_int8_t* fVPS; unsigned fVPSSize;
  u_int8_t* fSPS; unsigned fSPSSize;
  u_int8_t* fPPS; unsigned fPPSSize;
};

#endif
