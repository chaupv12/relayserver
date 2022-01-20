#ifndef _MPEG4_GENERIC_RTP_SOURCE_HH
#define _MPEG4_GENERIC_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class MPEG4GenericRTPSource: public MultiFramedRTPSource {
public:
  static MPEG4GenericRTPSource*
  createNew(BaseEnv& env, Groupsock* RTPgs,
	    unsigned char rtpPayloadFormat,
	    unsigned rtpTimestampFrequency,
	    char const* mediumName,
	    char const* mode, unsigned sizeLength, unsigned indexLength,
	    unsigned indexDeltaLength
	    // add other parameters later
	    );
  // mediumName is "audio", "video", or "application"
  // it *cannot* be NULL

protected:
  MPEG4GenericRTPSource(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat,
			unsigned rtpTimestampFrequency,
			char const* mediumName,
			char const* mode,
			unsigned sizeLength, unsigned indexLength,
			unsigned indexDeltaLength
			);
      // called only by createNew(), or by subclass constructors
  virtual ~MPEG4GenericRTPSource();

protected:
  // redefined virtual functions:
  virtual Boolean processSpecialHeader(BufferedPacket* packet,
                                       unsigned& resultSpecialHeaderSize);
  virtual char const* MIMEtype() const;

private:
  char* fMIMEType;

  char* fMode;
  unsigned fSizeLength, fIndexLength, fIndexDeltaLength;
  unsigned fNumAUHeaders; // in the most recently read packet
  unsigned fNextAUHeader; // index of the next AU Header to read
  struct AUHeader* fAUHeaders;

  friend class MPEG4GenericBufferedPacket;
};



// A function that looks up the sampling frequency from an
// "AudioSpecificConfig" string.  (0 means 'unknown')
unsigned samplingFrequencyFromAudioSpecificConfig(char const* configStr);

#endif
