#ifndef _MPEG_1OR2_DEMUXED_ELEMENTARY_STREAM_HH
#define _MPEG_1OR2_DEMUXED_ELEMENTARY_STREAM_HH

#ifndef _MPEG_1OR2_DEMUX_HH
#include "MPEG1or2Demux.hh"
#endif

class MPEG1or2DemuxedElementaryStream: public FramedSource {
public:
  MPEG1or2Demux::SCR lastSeenSCR() const { return fLastSeenSCR; }

  unsigned char mpegVersion() const { return fMPEGversion; }

  MPEG1or2Demux& sourceDemux() const { return fOurSourceDemux; }

private: // We are created only by a MPEG1or2Demux (a friend)
  MPEG1or2DemuxedElementaryStream(BaseEnv& env,
			      u_int8_t streamIdTag,
			      MPEG1or2Demux& sourceDemux);
  virtual ~MPEG1or2DemuxedElementaryStream();

private:
  // redefined virtual functions:
  virtual void doGetNextFrame();
  virtual void doStopGettingFrames();
  virtual char const* MIMEtype() const;
  virtual unsigned maxFrameSize() const;

private:
  static void afterGettingFrame(void* clientData,
				unsigned frameSize, unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);

  void afterGettingFrame1(unsigned frameSize, unsigned numTruncatedBytes,
			  struct timeval presentationTime,
			  unsigned durationInMicroseconds);

private:
  u_int8_t fOurStreamIdTag;
  MPEG1or2Demux& fOurSourceDemux;
  char const* fMIMEtype;
  MPEG1or2Demux::SCR fLastSeenSCR;
  unsigned char fMPEGversion;

  friend class MPEG1or2Demux;
};

#endif
