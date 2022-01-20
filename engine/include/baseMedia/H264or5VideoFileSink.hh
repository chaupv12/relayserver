#ifndef _H264_OR_5_VIDEO_FILE_SINK_HH
#define _H264_OR_5_VIDEO_FILE_SINK_HH

#ifndef _FILE_SINK_HH
#include "FileSink.hh"
#endif

class H264or5VideoFileSink: public FileSink {
protected:
  H264or5VideoFileSink(BaseEnv& env, FILE* fid,
		       unsigned bufferSize, char const* perFrameFileNamePrefix,
		       char const* sPropParameterSetsStr1,
		       char const* sPropParameterSetsStr2 = NULL,
		       char const* sPropParameterSetsStr3 = NULL);
      // we're an abstract base class
  virtual ~H264or5VideoFileSink();

protected: // redefined virtual functions:
  virtual void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes, struct timeval presentationTime);

private:
  char const* fSPropParameterSetsStr[3];
  Boolean fHaveWrittenFirstFrame;
};

#endif
