#ifndef _MPEG1or2_VIDEO_STREAM_DISCRETE_FRAMER_HH
#define _MPEG1or2_VIDEO_STREAM_DISCRETE_FRAMER_HH

#ifndef _MPEG1or2_VIDEO_STREAM_FRAMER_HH
#include "MPEG1or2VideoStreamFramer.hh"
#endif

#define VSH_MAX_SIZE 1000

class MPEG1or2VideoStreamDiscreteFramer: public MPEG1or2VideoStreamFramer {
public:
  static MPEG1or2VideoStreamDiscreteFramer*
  createNew(BaseEnv& env, FramedSource* inputSource,
            Boolean iFramesOnly = False, // see MPEG1or2VideoStreamFramer.hh
            double vshPeriod = 5.0, // see MPEG1or2VideoStreamFramer.hh
	    Boolean leavePresentationTimesUnmodified = False);

protected:
  MPEG1or2VideoStreamDiscreteFramer(BaseEnv& env,
                                    FramedSource* inputSource,
                                    Boolean iFramesOnly, double vshPeriod, Boolean leavePresentationTimesUnmodified);
  // called only by createNew()
  virtual ~MPEG1or2VideoStreamDiscreteFramer();

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

protected:
  Boolean fLeavePresentationTimesUnmodified;
  struct timeval fLastNonBFramePresentationTime;
  unsigned fLastNonBFrameTemporal_reference;

  // A saved copy of the most recently seen 'video_sequence_header',
  // in case we need to insert it into the stream periodically:
  unsigned char fSavedVSHBuffer[VSH_MAX_SIZE];
  unsigned fSavedVSHSize;
  double fSavedVSHTimestamp;
  Boolean fIFramesOnly;
  double fVSHPeriod;
};

#endif
