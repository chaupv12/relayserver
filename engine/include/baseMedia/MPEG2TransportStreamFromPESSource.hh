#ifndef _MPEG2_TRANSPORT_STREAM_FROM_PES_SOURCE_HH
#define _MPEG2_TRANSPORT_STREAM_FROM_PES_SOURCE_HH

#ifndef _MPEG2_TRANSPORT_STREAM_MULTIPLEXOR_HH
#include "MPEG2TransportStreamMultiplexor.hh"
#endif
#ifndef _MPEG_1OR2_DEMUXED_ELEMENTARY_STREAM_HH
#include "MPEG1or2DemuxedElementaryStream.hh"
#endif

class MPEG2TransportStreamFromPESSource: public MPEG2TransportStreamMultiplexor {
public:
  static MPEG2TransportStreamFromPESSource*
  createNew(BaseEnv& env, MPEG1or2DemuxedElementaryStream* inputSource);

protected:
  MPEG2TransportStreamFromPESSource(BaseEnv& env,
				    MPEG1or2DemuxedElementaryStream* inputSource);
      // called only by createNew()
  virtual ~MPEG2TransportStreamFromPESSource();

private:
  // Redefined virtual functions:
  virtual void doStopGettingFrames();
  virtual void awaitNewBuffer(unsigned char* oldBuffer);

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
  MPEG1or2DemuxedElementaryStream* fInputSource;
  unsigned char* fInputBuffer;
};

#endif
