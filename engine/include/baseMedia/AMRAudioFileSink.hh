#ifndef _AMR_AUDIO_FILE_SINK_HH
#define _AMR_AUDIO_FILE_SINK_HH

#ifndef _FILE_SINK_HH
#include "FileSink.hh"
#endif

class AMRAudioFileSink: public FileSink {
public:
  static AMRAudioFileSink* createNew(BaseEnv& env, char const* fileName,
				     unsigned bufferSize = 10000,
				     Boolean oneFilePerFrame = False);
  // (See "FileSink.hh" for a description of these parameters.)

protected:
  AMRAudioFileSink(BaseEnv& env, FILE* fid, unsigned bufferSize,
		   char const* perFrameFileNamePrefix);
      // called only by createNew()
  virtual ~AMRAudioFileSink();

protected: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);
  virtual void afterGettingFrame(unsigned frameSize,
				 unsigned numTruncatedBytes,
				 struct timeval presentationTime);

protected:
  Boolean fHaveWrittenHeader;
};

#endif
