#ifndef _H264_OR_5_VIDEO_STREAM_DISCRETE_FRAMER_HH
#define _H264_OR_5_VIDEO_STREAM_DISCRETE_FRAMER_HH

#ifndef _H264_OR_5_VIDEO_STREAM_FRAMER_HH
#include "H264or5VideoStreamFramer.hh"
#endif

class H264or5VideoStreamDiscreteFramer: public H264or5VideoStreamFramer {
protected:
  H264or5VideoStreamDiscreteFramer(int hNumber, BaseEnv& env, FramedSource* inputSource,
				   Boolean includeStartCodeInOutput,
				   Boolean insertAccessUnitDelimiters);
      // we're an abstract base class
  virtual ~H264or5VideoStreamDiscreteFramer();

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

  virtual Boolean nalUnitEndsAccessUnit(u_int8_t nal_unit_type);
};

#endif
