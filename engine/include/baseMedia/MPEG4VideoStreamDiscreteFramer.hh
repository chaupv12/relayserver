#ifndef _MPEG4_VIDEO_STREAM_DISCRETE_FRAMER_HH
#define _MPEG4_VIDEO_STREAM_DISCRETE_FRAMER_HH

#ifndef _MPEG4_VIDEO_STREAM_FRAMER_HH
#include "MPEG4VideoStreamFramer.hh"
#endif

class MPEG4VideoStreamDiscreteFramer: public MPEG4VideoStreamFramer {
public:
  static MPEG4VideoStreamDiscreteFramer*
  createNew(BaseEnv& env, FramedSource* inputSource, Boolean leavePresentationTimesUnmodified = False);

protected:
  MPEG4VideoStreamDiscreteFramer(BaseEnv& env,
				 FramedSource* inputSource, Boolean leavePresentationTimesUnmodified);
      // called only by createNew()
  virtual ~MPEG4VideoStreamDiscreteFramer();

protected:
  // redefined virtual functions:
  virtual void doGetNextFrame();

protected:
  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
                                struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize,
                          unsigned numTruncatedBytes,
                          struct timeval presentationTime,
                          unsigned durationInMicroseconds);

  Boolean getNextFrameBit(u_int8_t& result);
  Boolean getNextFrameBits(unsigned numBits, u_int32_t& result);
    // Which are used by:
  void analyzeVOLHeader();

protected:
  Boolean fLeavePresentationTimesUnmodified;
  u_int32_t vop_time_increment_resolution;
  unsigned fNumVTIRBits;
  // # of bits needed to count to "vop_time_increment_resolution"
  struct timeval fLastNonBFramePresentationTime;
  unsigned fLastNonBFrameVop_time_increment;

private:
  unsigned fNumBitsSeenSoFar; // used by the getNextFrameBit*() routines
};

#endif
