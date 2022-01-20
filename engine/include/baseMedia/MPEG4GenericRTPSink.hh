#ifndef _MPEG4_GENERIC_RTP_SINK_HH
#define _MPEG4_GENERIC_RTP_SINK_HH

#ifndef _MULTI_FRAMED_RTP_SINK_HH
#include "MultiFramedRTPSink.hh"
#endif

class MPEG4GenericRTPSink: public MultiFramedRTPSink {
public:
  static MPEG4GenericRTPSink*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    u_int8_t rtpPayloadFormat, u_int32_t rtpTimestampFrequency,
	    char const* sdpMediaTypeString, char const* mpeg4Mode,
	    char const* configString,
	    unsigned numChannels = 1);

protected:
  MPEG4GenericRTPSink(BaseEnv& env, Groupsock* RTPgs,
		      u_int8_t rtpPayloadFormat,
		      u_int32_t rtpTimestampFrequency,
		      char const* sdpMediaTypeString,
		      char const* mpeg4Mode, char const* configString,
		      unsigned numChannels);
	// called only by createNew()

  virtual ~MPEG4GenericRTPSink();

private: // redefined virtual functions:
  virtual
  Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
					 unsigned numBytesInFrame) const;
  virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
                                      unsigned char* frameStart,
                                      unsigned numBytesInFrame,
                                      struct timeval framePresentationTime,
                                      unsigned numRemainingBytes);
  virtual unsigned specialHeaderSize() const;

  virtual char const* sdpMediaType() const;

  virtual char const* auxSDPLine(); // for the "a=fmtp:" SDP line

private:
  char const* fSDPMediaTypeString;
  char const* fMPEG4Mode;
  char const* fConfigString;
  char* fFmtpSDPLine;
};

#endif
