#ifndef _VORBIS_AUDIO_RTP_SOURCE_HH
#define _VORBIS_AUDIO_RTP_SOURCE_HH

#ifndef _MULTI_FRAMED_RTP_SOURCE_HH
#include "MultiFramedRTPSource.hh"
#endif

class VorbisAudioRTPSource : public MultiFramedRTPSource {
public:
	static VorbisAudioRTPSource*
		createNew(BaseEnv& env, Groupsock* RTPgs,
			unsigned char rtpPayloadFormat,
			unsigned rtpTimestampFrequency);

	u_int32_t curPacketIdent() const { return fCurPacketIdent; } // The current "Ident" field; only the low-order 24 bits are used

protected:
	VorbisAudioRTPSource(BaseEnv& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency);
	// called only by createNew()

	virtual ~VorbisAudioRTPSource();

protected:
	// redefined virtual functions:
	virtual Boolean processSpecialHeader(BufferedPacket* packet,
		unsigned& resultSpecialHeaderSize);
	virtual char const* MIMEtype() const;

private:
	u_int32_t fCurPacketIdent; // only the low-order 24 bits are used
};

void parseVorbisOrTheoraConfigStr(char const* configStr,
	u_int8_t*& identificationHdr, unsigned& identificationHdrSize,
	u_int8_t*& commentHdr, unsigned& commentHdrSize,
	u_int8_t*& setupHdr, unsigned& setupHdrSize,
	u_int32_t& identField);
// Returns (in each of the result parameters) unpacked Vorbis or Theora
// "identification", "comment", and "setup" headers that were specified in a
// "config" string (in the SDP description for a Vorbis/RTP or Theora/RTP stream).
// Each of the "*Hdr" result arrays are dynamically allocated by this routine,
// and must be delete[]d by the caller.

#endif
