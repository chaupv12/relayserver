#ifndef _VORBIS_AUDIO_RTP_SINK_HH
#define _VORBIS_AUDIO_RTP_SINK_HH

#ifndef _AUDIO_RTP_SINK_HH
#include "AudioRTPSink.hh"
#endif

class VorbisAudioRTPSink : public AudioRTPSink {
public:
	static VorbisAudioRTPSink*
		createNew(BaseEnv& env, Groupsock* RTPgs, u_int8_t rtpPayloadFormat,
			u_int32_t rtpTimestampFrequency, unsigned numChannels,
			// The following headers provide the 'configuration' information, for the SDP description:
			u_int8_t* identificationHeader, unsigned identificationHeaderSize,
			u_int8_t* commentHeader, unsigned commentHeaderSize,
			u_int8_t* setupHeader, unsigned setupHeaderSize,
			u_int32_t identField = 0xFACADE);

	static VorbisAudioRTPSink*
		createNew(BaseEnv& env, Groupsock* RTPgs, u_int8_t rtpPayloadFormat,
			u_int32_t rtpTimestampFrequency, unsigned numChannels,
			char const* configStr);
	// an optional variant of "createNew()" that takes a Base-64-encoded 'configuration' string,
	// rather than the raw configuration headers as parameter.

protected:
	VorbisAudioRTPSink(BaseEnv& env, Groupsock* RTPgs,
		u_int8_t rtpPayloadFormat, u_int32_t rtpTimestampFrequency, unsigned numChannels,
		u_int8_t* identificationHeader, unsigned identificationHeaderSize,
		u_int8_t* commentHeader, unsigned commentHeaderSize,
		u_int8_t* setupHeader, unsigned setupHeaderSize,
		u_int32_t identField);
	// called only by createNew()

	virtual ~VorbisAudioRTPSink();

private: // redefined virtual functions:
	virtual char const* auxSDPLine(); // for the "a=fmtp:" SDP line

	virtual void doSpecialFrameHandling(unsigned fragmentationOffset,
		unsigned char* frameStart,
		unsigned numBytesInFrame,
		struct timeval framePresentationTime,
		unsigned numRemainingBytes);
	virtual Boolean frameCanAppearAfterPacketStart(unsigned char const* frameStart,
		unsigned numBytesInFrame) const;
	virtual unsigned specialHeaderSize() const;
	virtual unsigned frameSpecificHeaderSize() const;

private:
	u_int32_t fIdent; // "Ident" field used by this stream.  (Only the low 24 bits of this are used.)
	char* fFmtpSDPLine;
};


// A general function used by both "VorbisAudioRTPSink" and "TheoraVideoRTPSink" to construct
// a Base64-encoded 'config' string (for SDP) from "identification", "comment", "setup" headers.
// (Note: The result string was heap-allocated, and the caller should delete[] it afterwards.)

char* generateVorbisOrTheoraConfigStr(u_int8_t* identificationHeader, unsigned identificationHeaderSize,
	u_int8_t* commentHeader, unsigned commentHeaderSize,
	u_int8_t* setupHeader, unsigned setupHeaderSize,
	u_int32_t identField);

#endif
