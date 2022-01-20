#ifndef _MPEG2_TRANSPORT_STREAM_FROM_ES_SOURCE_HH
#define _MPEG2_TRANSPORT_STREAM_FROM_ES_SOURCE_HH

#ifndef _MPEG2_TRANSPORT_STREAM_MULTIPLEXOR_HH
#include "MPEG2TransportStreamMultiplexor.hh"
#endif

class MPEG2TransportStreamFromESSource: public MPEG2TransportStreamMultiplexor {
public:
  static MPEG2TransportStreamFromESSource* createNew(BaseEnv& env);

  void addNewVideoSource(FramedSource* inputSource, int mpegVersion, int16_t PID = -1);
      // Note: For MPEG-4 video, set "mpegVersion" to 4; for H.264 video, set "mpegVersion" to 5;
      //     for H.265 video, set "mpegVersion" to 6
  void addNewAudioSource(FramedSource* inputSource, int mpegVersion, int16_t PID = -1);
      // Note: For Opus audio, set "mpegVersion" to 3
  
      // Note: In these functions, if "PID" is not -1, then it (currently, just the low 8 bits)
      // is used as the stream's PID.  Otherwise (if "PID" is -1) the 'stream_id' is used as
      // the PID.

  static unsigned maxInputESFrameSize;

protected:
  MPEG2TransportStreamFromESSource(BaseEnv& env);
      // called only by createNew()
  virtual ~MPEG2TransportStreamFromESSource();

  void addNewInputSource(FramedSource* inputSource,
			 u_int8_t streamId, int mpegVersion, int16_t PID = -1);
  // used to implement addNew*Source() above

private:
  // Redefined virtual functions:
  virtual void doStopGettingFrames();
  virtual void awaitNewBuffer(unsigned char* oldBuffer);

private:
  friend class InputESSourceRecord;
  class InputESSourceRecord* fInputSources;
  unsigned fVideoSourceCounter, fAudioSourceCounter;
  Boolean fAwaitingBackgroundDelivery;
};

#endif
