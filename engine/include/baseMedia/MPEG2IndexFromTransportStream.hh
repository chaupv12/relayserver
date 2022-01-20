#ifndef _MPEG2_IFRAME_INDEX_FROM_TRANSPORT_STREAM_HH
#define _MPEG2_IFRAME_INDEX_FROM_TRANSPORT_STREAM_HH

#ifndef _FRAMED_FILTER_HH
#include "FramedFilter.hh"
#endif

#ifndef TRANSPORT_PACKET_SIZE
#define TRANSPORT_PACKET_SIZE 188
#endif

#ifndef MAX_PES_PACKET_SIZE
#define MAX_PES_PACKET_SIZE 65536
#endif

class IndexRecord; // forward

class MPEG2IFrameIndexFromTransportStream: public FramedFilter {
public:
  static MPEG2IFrameIndexFromTransportStream*
  createNew(BaseEnv& env, FramedSource* inputSource);

protected:
  MPEG2IFrameIndexFromTransportStream(BaseEnv& env,
				      FramedSource* inputSource);
      // called only by createNew()
  virtual ~MPEG2IFrameIndexFromTransportStream();

private:
  // Redefined virtual functions:
  virtual void doGetNextFrame();

private:
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  void afterGettingFrame1(unsigned frameSize,
			  unsigned numTruncatedBytes,
			  struct timeval presentationTime,
			  unsigned durationInMicroseconds);

  static void handleInputClosure(void* clientData);
  void handleInputClosure1();

  void analyzePAT(unsigned char* pkt, unsigned size);
  void analyzePMT(unsigned char* pkt, unsigned size);

  Boolean deliverIndexRecord();
  Boolean parseFrame();
  Boolean parseToNextCode(unsigned char& nextCode);
  void compactParseBuffer();
  void addToTail(IndexRecord* newIndexRecord);

private:
  Boolean fIsH264; // True iff the video is H.264 (encapsulated in a Transport Stream)
  Boolean fIsH265; // True iff the video is H.265 (encapsulated in a Transport Stream)
  unsigned long fInputTransportPacketCounter;
  unsigned fClosureNumber;
  u_int8_t fLastContinuityCounter;
  float fFirstPCR, fLastPCR;
  Boolean fHaveSeenFirstPCR;
  u_int16_t fPMT_PID, fVideo_PID;
      // Note: We assume: 1 program per Transport Stream; 1 video stream per program
  unsigned char fInputBuffer[TRANSPORT_PACKET_SIZE];
  unsigned char* fParseBuffer;
  unsigned fParseBufferSize;
  unsigned fParseBufferFrameStart;
  unsigned fParseBufferParseEnd;
  unsigned fParseBufferDataEnd;
  IndexRecord* fHeadIndexRecord;
  IndexRecord* fTailIndexRecord;
};

#endif
