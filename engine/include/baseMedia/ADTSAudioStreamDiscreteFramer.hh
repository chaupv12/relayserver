#ifndef _ADTS_AUDIO_STREAM_DISCRETE_FRAMER_HH
#define _ADTS_AUDIO_STREAM_DISCRETE_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#define ADTS_HEADER_SIZE 7 // we don't include a checksum

class ADTSAudioStreamDiscreteFramer: public FramedFilter {
public:
  static ADTSAudioStreamDiscreteFramer*
  createNew(BaseEnv& env, FramedSource* inputSource, char const* configStr);
    // "configStr" should be a 4-character hexadecimal string for a 2-byte value

protected:
  ADTSAudioStreamDiscreteFramer(BaseEnv& env, FramedSource* inputSource,
				u_int8_t profile, u_int8_t samplingFrequencyIndex, u_int8_t channelConfiguration);
      // called only by createNew()
  virtual ~ADTSAudioStreamDiscreteFramer();

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

private:
  u_int8_t fADTSHeader[ADTS_HEADER_SIZE];
};

#endif
