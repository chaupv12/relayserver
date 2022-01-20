#ifndef _QCELP_AUDIO_RTP_SOURCE_HH
#define _QCELP_AUDIO_RTP_SOURCE_HH

#ifndef _RTP_SOURCE_HH
#include "RTPSource.hh"
#endif

class QCELPAudioRTPSource {
public:
	static FramedSource* createNew(BaseEnv& env,
		Groupsock* RTPgs,
		RTPSource*& resultRTPSource,
		unsigned char rtpPayloadFormat = 12,
		unsigned rtpTimestampFrequency = 8000);
	// This returns a source to read from, but "resultRTPSource" will
	// point to RTP-related state.
};

#endif
