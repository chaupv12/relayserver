#ifndef _BYTE_STREAM_MEMORY_BUFFER_SOURCE_HH
#define _BYTE_STREAM_MEMORY_BUFFER_SOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

class ByteStreamMemoryBufferSource: public FramedSource {
public:
  static ByteStreamMemoryBufferSource* createNew(BaseEnv& env,
						 u_int8_t* buffer, u_int64_t bufferSize,
						 Boolean deleteBufferOnClose = True,
						 unsigned preferredFrameSize = 0,
						 unsigned playTimePerFrame = 0);
      // "preferredFrameSize" == 0 means 'no preference'
      // "playTimePerFrame" is in microseconds

  u_int64_t bufferSize() const { return fBufferSize; }

  void seekToByteAbsolute(u_int64_t byteNumber, u_int64_t numBytesToStream = 0);
    // if "numBytesToStream" is >0, then we limit the stream to that number of bytes, before treating it as EOF
  void seekToByteRelative(int64_t offset, u_int64_t numBytesToStream = 0);

protected:
  ByteStreamMemoryBufferSource(BaseEnv& env,
			       u_int8_t* buffer, u_int64_t bufferSize,
			       Boolean deleteBufferOnClose,
			       unsigned preferredFrameSize,
			       unsigned playTimePerFrame);
	// called only by createNew()

  virtual ~ByteStreamMemoryBufferSource();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();

private:
  u_int8_t* fBuffer;
  u_int64_t fBufferSize;
  u_int64_t fCurIndex;
  Boolean fDeleteBufferOnClose;
  unsigned fPreferredFrameSize;
  unsigned fPlayTimePerFrame;
  unsigned fLastPlayTime;
  Boolean fLimitNumBytesToStream;
  u_int64_t fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True
};

#endif
