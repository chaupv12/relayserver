#ifndef _MPEG_VIDEO_STREAM_FRAMER_HH
#define _MPEG_VIDEO_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

class TimeCode {
public:
  TimeCode();
  virtual ~TimeCode();

  int operator==(TimeCode const& arg2);
  unsigned days, hours, minutes, seconds, pictures;
};

class MPEGVideoStreamFramer: public FramedFilter {
public:
  Boolean& pictureEndMarker() { return fPictureEndMarker; }
      // a hack for implementing the RTP 'M' bit

  void flushInput(); // called if there is a discontinuity (seeking) in the input

protected:
  MPEGVideoStreamFramer(BaseEnv& env, FramedSource* inputSource);
      // we're an abstract base class
  virtual ~MPEGVideoStreamFramer();

  void computePresentationTime(unsigned numAdditionalPictures);
      // sets "fPresentationTime"
  void setTimeCode(unsigned hours, unsigned minutes, unsigned seconds,
		   unsigned pictures, unsigned picturesSinceLastGOP);

protected: // redefined virtual functions
  virtual void doGetNextFrame();
  virtual void doStopGettingFrames();

private:
  void reset();

  static void continueReadProcessing(void* clientData,
				     unsigned char* ptr, unsigned size,
				     struct timeval presentationTime);
  void continueReadProcessing();

protected:
  double fFrameRate; // Note: For MPEG-4, this is really a 'tick rate'
  unsigned fPictureCount; // hack used to implement doGetNextFrame()
  Boolean fPictureEndMarker;
  struct timeval fPresentationTimeBase;

  // parsing state
  class MPEGVideoStreamParser* fParser;
  friend class MPEGVideoStreamParser; // hack

private:
  TimeCode fCurGOPTimeCode, fPrevGOPTimeCode;
  unsigned fPicturesAdjustment;
  double fPictureTimeBase;
  unsigned fTcSecsBase;
  Boolean fHaveSeenFirstTimeCode;
};

#endif
