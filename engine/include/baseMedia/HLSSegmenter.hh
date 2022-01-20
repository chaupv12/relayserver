#ifndef _HLS_SEGMENTER_HH
#define _HLS_SEGMENTER_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif

class HLSSegmenter: public MediaSink {
public:
  typedef void (onEndOfSegmentFunc)(void* clientData,
				    char const* segmentFileName, double segmentDuration);
  static HLSSegmenter* createNew(BaseEnv& env,
				 unsigned segmentationDuration, char const* fileNamePrefix,
				 onEndOfSegmentFunc* onEndOfSegmentFunc = NULL,
				 void* onEndOfSegmentClientData = NULL);

private:
  HLSSegmenter(BaseEnv& env, unsigned segmentationDuration, char const* fileNamePrefix,
	       onEndOfSegmentFunc* onEndOfSegmentFunc, void* onEndOfSegmentClientData);
    // called only by createNew()
  virtual ~HLSSegmenter();

  static void ourEndOfSegmentHandler(void* clientData, double segmentDuration);
  void ourEndOfSegmentHandler(double segmentDuration);

  Boolean openNextOutputSegment();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
                                struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  virtual void afterGettingFrame(unsigned frameSize,
                                 unsigned numTruncatedBytes);

  static void ourOnSourceClosure(void* clientData);
  void ourOnSourceClosure();

private: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);
  virtual Boolean continuePlaying();

private:
  unsigned fSegmentationDuration;
  char const* fFileNamePrefix;
  onEndOfSegmentFunc* fOnEndOfSegmentFunc;
  void* fOnEndOfSegmentClientData;
  Boolean fHaveConfiguredUpstreamSource;
  unsigned fCurrentSegmentCounter;
  char* fOutputSegmentFileName;
  FILE* fOutFid;
  unsigned char* fOutputFileBuffer;
};

#endif
