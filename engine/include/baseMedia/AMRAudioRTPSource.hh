#ifndef _AMR_AUDIO_RTP_SOURCE_HH
#define _AMR_AUDIO_RTP_SOURCE_HH

#ifndef _RTP_SOURCE_HH
#include "RTPSource.hh"
#endif
#ifndef _AMR_AUDIO_SOURCE_HH
#include "AMRAudioSource.hh"
#endif

class AMRAudioRTPSource {
public:
  static AMRAudioSource* createNew(BaseEnv& env,
				   Groupsock* RTPgs,
				   RTPSource*& resultRTPSource,
				   unsigned char rtpPayloadFormat,
				   Boolean isWideband = False,
				   unsigned numChannels = 1,
				   Boolean isOctetAligned = True,
				   unsigned interleaving = 0,
				     // relevant only if "isOctetAligned"
				     // The maximum # of frame-blocks in a group
				     // 0 means: no interleaving
				   Boolean robustSortingOrder = False,
				     // relevant only if "isOctetAligned"
				   Boolean CRCsArePresent = False
				     // relevant only if "isOctetAligned"
				   );
      // This returns a source to read from, but "resultRTPSource" will
      // point to RTP-related state.
};

#endif
