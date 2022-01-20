#ifndef _MPEG2_TRANSPORT_STREAM_ACCUMULATOR_HH
#define _MPEG2_TRANSPORT_STREAM_ACCUMULATOR_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class MPEG2TransportStreamAccumulator: public FramedFilter {
public:
  static MPEG2TransportStreamAccumulator* createNew(BaseEnv& env,
						    FramedSource* inputSource,
						    unsigned maxPacketSize = 1456);

protected:
  MPEG2TransportStreamAccumulator(BaseEnv& env,
				  FramedSource* inputSource, unsigned maxPacketSize);
      // called only by createNew()
  virtual ~MPEG2TransportStreamAccumulator();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();

private:
  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
                                struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize,
                          unsigned numTruncatedBytes,
                          struct timeval presentationTime,
                          unsigned durationInMicroseconds);

private:
  unsigned const fDesiredPacketSize;
  unsigned fNumBytesGathered;
};

#endif
