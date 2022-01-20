#ifndef _ADTS_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _ADTS_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class ADTSAudioFileServerMediaSubsession : public FileServerMediaSubsession {
public:
	static ADTSAudioFileServerMediaSubsession*
		createNew(BaseEnv& env, char const* fileName, Boolean reuseFirstSource);

protected:
	ADTSAudioFileServerMediaSubsession(BaseEnv& env,
		char const* fileName, Boolean reuseFirstSource);
	// called only by createNew();
	virtual ~ADTSAudioFileServerMediaSubsession();

protected: // redefined virtual functions
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
		unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
		unsigned char rtpPayloadTypeIfDynamic,
		FramedSource* inputSource);
};

#endif
