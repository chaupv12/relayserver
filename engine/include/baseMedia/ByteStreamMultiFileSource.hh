#ifndef _BYTE_STREAM_MULTI_FILE_SOURCE_HH
#define _BYTE_STREAM_MULTI_FILE_SOURCE_HH

#ifndef _BYTE_STREAM_FILE_SOURCE_HH
#include "ByteStreamFileSource.hh"
#endif

class ByteStreamMultiFileSource: public FramedSource {
public:
  static ByteStreamMultiFileSource*
  createNew(BaseEnv& env, char const** fileNameArray,
	    unsigned preferredFrameSize = 0, unsigned playTimePerFrame = 0);
  // "fileNameArray" is a pointer to an array of (char const*) file names, with
  // A 'file name' of NULL indicating the end of the array

  Boolean haveStartedNewFile() const { return fHaveStartedNewFile; }
  // True iff the most recently delivered frame was the first from a newly-opened file

protected:
  ByteStreamMultiFileSource(BaseEnv& env, char const** fileNameArray,
			    unsigned preferredFrameSize, unsigned playTimePerFrame);
	// called only by createNew()

  virtual ~ByteStreamMultiFileSource();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();

private:
  static void onSourceClosure(void* clientData);
  void onSourceClosure1();
  static void afterGettingFrame(void* clientData,
				unsigned frameSize, unsigned numTruncatedBytes,
                                struct timeval presentationTime,
				unsigned durationInMicroseconds);

private:
  unsigned fPreferredFrameSize;
  unsigned fPlayTimePerFrame;
  unsigned fNumSources;
  unsigned fCurrentlyReadSourceNumber;
  Boolean fHaveStartedNewFile;
  char const** fFileNameArray;
  ByteStreamFileSource** fSourceArray;
};

#endif
