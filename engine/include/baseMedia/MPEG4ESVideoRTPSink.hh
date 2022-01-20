#ifndef _MPEG4ES_VIDEO_RTP_SINK_HH
#define _MPEG4ES_VIDEO_RTP_SINK_HH

#ifndef _VIDEO_RTP_SINK_HH
#include "VideoRTPSink.hh"
#endif

class MPEG4ESVideoRTPSink: public VideoRTPSink {
public:
  static MPEG4ESVideoRTPSink* createNew(BaseEnv& env,
					Groupsock* RTPgs, unsigned char rtpPayloadFormat,
					u_int32_t rtpTimestampFrequency = 90000);
  static MPEG4ESVideoRTPSink* createNew(BaseEnv& env,
					Groupsock* RTPgs, unsigned char rtpPayloadFormat, u_int32_t rtpTimestampFrequency,
					u_int8_t profileAndLevelIndication, char const* configStr);
    // an optional variant of "createNew()", useful if we know, in advance, the stream's 'configuration' info.


protected:
  MPEG4ESVideoRTPSink(BaseEnv& env, Groupsock* RTPgs, unsigned char rtpPayloadFormat, u_int32_t rtpTimestampFrequency,
		      u_int8_t profileAndLevelIndication = 0, char const* configStr = NULL);
	// called only by createNew()

  virtual ~MPEG4ESVideoRTPSink();

protected: // redefined virtual functions:
  virtual Boolean sourceIsCompatibleWithUs(MediaSource& source);

  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual Boolean allowFragmentationAfterStart() const;
  virtual Boolean
  frameCanAppearAfterPacketStart(unsigned char const* frameStart,
				 unsigned numBytesInFrame) const;

  virtual char const* auxSDPLine();

protected:
  Boolean fVOPIsPresent;

private:
  u_int8_t fProfileAndLevelIndication;
  unsigned char* fConfigBytes;
  unsigned fNumConfigBytes;

  char* fFmtpSDPLine;
};

#endif
