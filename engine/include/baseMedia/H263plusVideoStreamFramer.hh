#ifndef _H263PLUS_VIDEO_STREAM_FRAMER_HH
#define _H263PLUS_VIDEO_STREAM_FRAMER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif


class H263plusVideoStreamFramer: public FramedFilter {
public:

  static H263plusVideoStreamFramer* createNew(BaseEnv& env, FramedSource* inputSource);

  Boolean& pictureEndMarker() { return fPictureEndMarker; }    // a hack for implementing the RTP 'M' bit

protected:
  // Constructor called only by createNew(), or by subclass constructors
  H263plusVideoStreamFramer(BaseEnv& env,
			                FramedSource* inputSource,
			                Boolean createParser = True);
  virtual ~H263plusVideoStreamFramer();


public:
  static void continueReadProcessing(void* clientData,
				     unsigned char* ptr, unsigned size,
				     struct timeval presentationTime);
  void continueReadProcessing();

private:
  virtual void doGetNextFrame();
  virtual Boolean isH263plusVideoStreamFramer() const;

protected:
  double   fFrameRate;
  unsigned fPictureCount; // hack used to implement doGetNextFrame() ??
  Boolean  fPictureEndMarker;

private:
  class H263plusVideoStreamParser* fParser;
  struct timeval fPresentationTimeBase;
};

#endif
