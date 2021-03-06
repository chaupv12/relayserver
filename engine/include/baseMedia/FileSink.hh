#ifndef _FILE_SINK_HH
#define _FILE_SINK_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif

class FileSink: public MediaSink {
public:
  static FileSink* createNew(BaseEnv& env, char const* fileName,
			     unsigned bufferSize = 20000,
			     Boolean oneFilePerFrame = False);
  // "bufferSize" should be at least as large as the largest expected
  //   input frame.
  // "oneFilePerFrame" - if True - specifies that each input frame will
  //   be written to a separate file (using the presentation time as a
  //   file name suffix).  The default behavior ("oneFilePerFrame" == False)
  //   is to output all incoming data into a single file.

  virtual void addData(unsigned char const* data, unsigned dataSize,
		       struct timeval presentationTime);
  // (Available in case a client wants to add extra data to the output file)

protected:
  FileSink(BaseEnv& env, FILE* fid, unsigned bufferSize,
	   char const* perFrameFileNamePrefix);
      // called only by createNew()
  virtual ~FileSink();

protected: // redefined virtual functions:
  virtual Boolean continuePlaying();

protected:
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  virtual void afterGettingFrame(unsigned frameSize,
				 unsigned numTruncatedBytes,
				 struct timeval presentationTime);

  FILE* fOutFid;
  unsigned char* fBuffer;
  unsigned fBufferSize;
  char* fPerFrameFileNamePrefix; // used if "oneFilePerFrame" is True
  char* fPerFrameFileNameBuffer; // used if "oneFilePerFrame" is True
  struct timeval fPrevPresentationTime;
  unsigned fSamePresentationTimeCounter;
};

#endif
