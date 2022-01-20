#ifndef _MPEG_1OR2_AUDIO_STREAM_FRAMER_HH
#define _MPEG_1OR2_AUDIO_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class MPEG1or2AudioStreamFramer: public FramedFilter {
public:
  static MPEG1or2AudioStreamFramer*
  createNew(BaseEnv& env, FramedSource* inputSource,
	    Boolean syncWithInputSource = False);
  // If "syncWithInputSource" is True, the stream's presentation time
  // will be reset to that of the input source, whenever new data
  // is read from it.

  void flushInput(); // called if there is a discontinuity (seeking) in the input

private:
  MPEG1or2AudioStreamFramer(BaseEnv& env, FramedSource* inputSource,
			    Boolean syncWithInputSource);
      // called only by createNew()
  virtual ~MPEG1or2AudioStreamFramer();

  static void continueReadProcessing(void* clientData,
				     unsigned char* ptr, unsigned size,
				     struct timeval presentationTime);
  void continueReadProcessing();

  void resetPresentationTime(struct timeval newPresentationTime);
      // useful if we're being synced with a separate (e.g., video) stream

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();

private:
  void reset();
  struct timeval currentFramePlayTime() const;

private:
  Boolean fSyncWithInputSource;
  struct timeval fNextFramePresentationTime;

private: // parsing state
  class MPEG1or2AudioStreamParser* fParser;
  friend class MPEG1or2AudioStreamParser; // hack
};

#endif
