#ifndef _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH
#define _MPEG2_TRANSPORT_STREAM_TRICK_MODE_FILTER_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef _MPEG2_TRANSPORT_STREAM_INDEX_FILE_HH
#include "MPEG2TransportStreamIndexFile.hh"
#endif

#ifndef TRANSPORT_PACKET_SIZE
#define TRANSPORT_PACKET_SIZE 188
#endif

class MPEG2TransportStreamTrickModeFilter: public FramedFilter {
public:
  static MPEG2TransportStreamTrickModeFilter*
  createNew(BaseEnv& env, FramedSource* inputSource,
	    MPEG2TransportStreamIndexFile* indexFile, int scale);

  Boolean seekTo(unsigned long tsPacketNumber, unsigned long indexRecordNumber);

  unsigned long nextIndexRecordNum() const { return fNextIndexRecordNum; }

  void forgetInputSource() { fInputSource = NULL; }
      // this lets us delete this without also deleting the input Transport Stream

protected:
  MPEG2TransportStreamTrickModeFilter(BaseEnv& env, FramedSource* inputSource,
				      MPEG2TransportStreamIndexFile* indexFile, int scale);
      // called only by createNew()
  virtual ~MPEG2TransportStreamTrickModeFilter();

private:
  // Redefined virtual functions:
  virtual void doGetNextFrame();
  virtual void doStopGettingFrames();

private:
  void attemptDeliveryToClient();
  void seekToTransportPacket(unsigned long tsPacketNum);
  void readTransportPacket(unsigned long tsPacketNum); // asynchronously

  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize);

  static void onSourceClosure(void* clientData);
  void onSourceClosure1();

private:
  Boolean fHaveStarted;
  MPEG2TransportStreamIndexFile* fIndexFile;
  int fScale; // absolute value
  int fDirection; // 1 => forward; -1 => reverse
  enum {
    SKIPPING_FRAME,
    DELIVERING_SAVED_FRAME,
    SAVING_AND_DELIVERING_FRAME
  } fState;
  unsigned fFrameCount;
  unsigned long fNextIndexRecordNum; // next to be read from the index file
  unsigned long fNextTSPacketNum; // next to be read from the transport stream file
  unsigned char fInputBuffer[TRANSPORT_PACKET_SIZE];
  unsigned long fCurrentTSPacketNum; // corresponding to data currently in the buffer
  unsigned long fDesiredTSPacketNum;
  u_int8_t fDesiredDataOffset, fDesiredDataSize;
  float fDesiredDataPCR, fFirstPCR;
  unsigned long fSavedFrameIndexRecordStart;
  unsigned long fSavedSequentialIndexRecordNum;
  Boolean fUseSavedFrameNextTime;
};

#endif
